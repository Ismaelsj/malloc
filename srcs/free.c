/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 15:33:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

t_block			*defragment_block(t_block *block, int t)
{
	t_block *tmp;

	if (block && block->next && block->size < get_pool_size(t)
		&& !block->next->busy)
	{
		tmp = block->next;
		block->next = tmp->next;
		if (tmp->next)
		{
			tmp->next->prev = block;
			lock_block(tmp->next);
		}
		block->size += tmp->size + align_size(sizeof(t_block), 16);
	}
	if (block && block->prev && block->size < get_pool_size(t)
		&& !block->prev->busy)
	{
		tmp = block;
		block = block->prev;
		block->next = tmp->next;
		if (tmp->next)
		{
			tmp->next->prev = block;
			lock_block(block->next);
		}
		block->size += tmp->size + align_size(sizeof(t_block), 16);
	}
	if (block && t < LARGE
		&& block->size >= (get_pool_size(t) + get_pool_size(t - 1)))
	{
		create_intermediate_block(block, get_pool_size(t), t, 0);
		if (block->next && !block->next->busy
			&& block->next->size >= (get_pool_size(t) + get_pool_size(t - 1)))
		{
			create_intermediate_block(block->next, get_pool_size(t), t, 0);
			lock_block(block->next);
		}
	}
	return (block);
}

void			free(void *ptr)
{
	t_block *block;
	t_area	*area;

	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_mutex);
	area = retrieve_area(ptr);
	block = retrieve_block(area, ptr);
	if (area && block)
		free_block(area, block);
	pthread_mutex_unlock(&g_mutex);
}

void			free_block(t_area *area, t_block *block)
{
	if (block == NULL || block->busy == 0)
		return ;
	area->occupied -= align_size(sizeof(t_block), 16) + block->size;
	block->busy = 0;
	block = defragment_block(block, area->type);
	lock_block(block);
	if (area->full)
		area->full = 0;
	if (area->occupied == 0)
		free_area(area);
	else
		lock_area(area);
}

void			free_area(t_area *area)
{
	t_area *prev_area;
	t_area *next_area;

	next_area = area->next;
	prev_area = area->prev;
	if (next_area)
	{
		next_area->prev = prev_area;
		lock_area(next_area);
	}
	if (prev_area)
	{
		prev_area->next = next_area;
		lock_area(prev_area);
	}
	if (next_area && prev_area == NULL)
		g_type[area->type].first_area = next_area;
	else if (next_area == NULL && prev_area == NULL)
		g_type[area->type].first_area = NULL;
	munmap((void *)area, area->size);
}
