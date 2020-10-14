/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 18:00:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int			check_prev(t_block *block, size_t size)
{
	if (block == NULL)
		return (0);
	if (block->prev != NULL && !block->prev->busy)
		if (block->prev->size + block->size >= size)
			return (1);
	return (0);
}

static void			*up_sizing_block(t_area *area, t_block *block, size_t size)
{
	size_t	original_size;
	void	*data;
	t_block	*new_block;

	original_size = block->size;
	data = BLOCK_MEM(block);
	if (block->size >= size)
	{
		pthread_mutex_unlock(&g_mutex);
		return (BLOCK_MEM(block));
	}
	if (check_prev(block, size))
	{
		block->busy = 0;
		block = block->prev;
		block->busy = 1;
	}
	if (check_mergeable_block(area, block, size))
	{
		ft_memcpy(BLOCK_MEM(block), data, original_size);
		lock_block(block);
		area->occupied += block->size - original_size;
		pthread_mutex_unlock(&g_mutex);
		return (BLOCK_MEM(block));
	}
	else
	{
		if ((new_block = check_free_area(choose_pool(size), size)) == NULL)
		{
			pthread_mutex_unlock(&g_mutex);
			return (NULL);
		}
		ft_memcpy(BLOCK_MEM(new_block), data, original_size);
		pthread_mutex_unlock(&g_mutex);
		free_block(area, block);
		return (BLOCK_MEM(new_block));
	}
}

static void			*down_sizing_block(t_area *area, t_block *block,\
										size_t size)
{
	size_t	original_size;
	void	*data;

	original_size = block->size;
	data = BLOCK_MEM(block);
	create_intermediate_block(block, size, area->type, 1);
	ft_memcpy(BLOCK_MEM(block), data, size);
	lock_block(block);
	area->occupied -= original_size - block->size;
	pthread_mutex_unlock(&g_mutex);
	return (BLOCK_MEM(block));
}

static void			*realloc_block(t_area *area, t_block *block, size_t size)
{
	size_t	aligned_size;

	aligned_size = align_size(size, 16);
	if (choose_pool(aligned_size) != area->type)
	{
		pthread_mutex_unlock(&g_mutex);
		free_block(area, block);
		return (malloc(size));
	}
	if (aligned_size < block->size)
	{
		if (area->type == LARGE)
		{
			pthread_mutex_unlock(&g_mutex);
			free_block(area, block);
			return (malloc(size));
		}
		return (down_sizing_block(area, block, aligned_size));
	}
	return (up_sizing_block(area, block, aligned_size));
}

void				*realloc(void *ptr, size_t size)
{
	t_area	*area;
	t_block	*block;

	if (ptr == NULL)
		return (malloc(size));
	else if (size == 0)
	{
		if (!ptr)
			return (NULL);
		free(ptr);
		return (malloc(16));
	}
	if ((area = retrieve_area(ptr)) == NULL)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	block = retrieve_block(area, ptr);
	if (block->busy == 0)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	return (realloc_block(area, block, size));
}
