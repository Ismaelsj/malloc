/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:05:27 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 11:29:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap			init_heap(int type, size_t size)
{
	t_area	*new_area;
	t_heap	new_heap;

	new_area = request_memory(0, get_page_size(type, size));
	init_area(new_area, NULL, size, type);
	new_heap.type = type;
	new_heap.first_area = new_area;
	lock_area(new_area);
	return (new_heap);
}

void			init_area(t_area *area, t_area *prev, size_t size, int type)
{
	area->first_block = (t_block *)AREA_MEM(area);
	area->size = get_page_size(type, size);
	area->type = type;
	area->unset_size = area->size;
	area->occupied = 0;
	area->full = 0;
	area->prev = prev;
	area->next = NULL;
	area->first_block->size = size;
	area->first_block->busy = 0;
	area->first_block->prev = NULL;
	area->first_block->next = NULL;
	lock_block(area->first_block);
	area->unset_size -= align_size(sizeof(t_block), 16)\
								+ area->first_block->size;
	lock_area(area);
}

void			init_block(t_block *block, size_t size)
{
	block->size = size;
	block->busy = 1;
	lock_block(block);
}
