/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 20:22:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	pthread_mutex_lock(&g_mutex);
	if ((area = retrieve_area(ptr)) == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		free(ptr);
		return (NULL);
	}
	if ((block = retrieve_block(area, ptr))->busy == 0)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	return (realloc_block(area, block, size));
}
