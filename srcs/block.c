/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 11:29:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*set_available_block(t_block *block, t_area *area, size_t size)
{
	block->busy = 1;
	create_intermediate_block(block, size, area->type, 1);
	init_block(block, size);
	return (block);
}

t_block			*check_free_block(t_area *area, size_t size)
{
	t_block *block;
	t_block *available_block;

	available_block = NULL;
	block = area->first_block;
	while (block)
	{
		if (get_block_crc32(block) != block->crc32)
			return (NULL);
		if (block->busy == 0 && block->size >= size
			&& (available_block == NULL || block->size < available_block->size))
			available_block = block;
		if (!block->next)
			break ;
		block = block->next;
	}
	if (available_block != NULL)
		return (set_available_block(available_block, area, size));
	if (area->unset_size < align_size(sizeof(t_block), 16) + size)
		return (NULL);
	block->next = append_new_block(block, size);
	lock_block(block);
	area->unset_size -= align_size(sizeof(t_block), 16) + block->next->size;
	return (block->next);
}

t_block			*append_new_block(t_block *prev, size_t size)
{
	t_block *new_block;

	new_block = BLOCK_NEXT(prev);
	new_block->size = size;
	new_block->prev = prev;
	new_block->next = NULL;
	new_block->busy = 1;
	lock_block(new_block);
	return (new_block);
}
