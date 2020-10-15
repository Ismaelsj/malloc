/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:30:53 by user42            #+#    #+#             */
/*   Updated: 2020/10/15 13:41:11 by user42           ###   ########.fr       */
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

static void			*create_new_block(t_area *area, t_block *block,\
							size_t size, size_t original_size)
{
	t_block	*new_block;

	if ((new_block = check_free_area(choose_pool(size), size)) == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	ft_memcpy(block_mem(new_block), block_mem(block), original_size);
	pthread_mutex_unlock(&g_mutex);
	free_block(area, block);
	return (block_mem(new_block));
}

void				*up_sizing_block(t_area *area, t_block *block, size_t size)
{
	size_t	original_size;

	original_size = block->size;
	if (block->size >= size)
	{
		pthread_mutex_unlock(&g_mutex);
		return (block_mem(block));
	}
	if (check_prev(block, size))
	{
		block->busy = 0;
		block = block->prev;
		block->busy = 1;
	}
	if (check_mergeable_block(area, block, size))
	{
		ft_memcpy(block_mem(block), block_mem(block), original_size);
		lock_block(block);
		area->occupied += block->size - original_size;
		pthread_mutex_unlock(&g_mutex);
		return (block_mem(block));
	}
	else
		return (create_new_block(area, block, size, original_size));
}

void				*down_sizing_block(t_area *area, t_block *block,\
										size_t size)
{
	size_t	original_size;
	void	*data;

	original_size = block->size;
	data = block_mem(block);
	create_intermediate_block(block, size, area->type, 1);
	ft_memcpy(block_mem(block), data, size);
	lock_block(block);
	area->occupied -= original_size - block->size;
	pthread_mutex_unlock(&g_mutex);
	return (block_mem(block));
}
