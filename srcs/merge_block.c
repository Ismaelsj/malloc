/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:55:56 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 11:57:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		merge_existing_block(t_block *block, size_t size, int type)
{
	size_t	rest_size;

	if (block->size + block->next->size + align_size(sizeof(t_block), 16)
		>= size)
	{
		rest_size = block->next->size + block->size\
					+ align_size(sizeof(t_block), 16) - size;
		block->next = block->next->next;
		if (block->next)
		{
			block->next->prev = block;
			lock_block(block->next);
		}
		block->size = rest_size + size;
		block->busy = 1;
		create_intermediate_block(block, size, type, 1);
		lock_block(block);
		return (1);
	}
	return (0);
}

void			create_intermediate_block(t_block *block,\
								size_t wanted_size, int type, int defrag)
{
	t_block *rest;
	size_t	rest_size;

	rest_size = block->size - wanted_size;
	if (block->size > wanted_size && rest_size
		> align_size(sizeof(t_block), 16))
	{
		block->size = wanted_size;
		rest = block_next(block);
		rest->size = rest_size - align_size(sizeof(t_block), 16);
		rest->busy = 0;
		rest->prev = block;
		rest->next = block->next;
		if (rest->next)
		{
			rest->next->prev = rest;
			lock_block(rest->next);
		}
		if (defrag)
			rest = defragment_block(rest, type);
		block->next = rest;
		lock_block(rest);
		lock_block(block);
	}
}

int				check_mergeable_block(t_area *area, t_block *block, size_t size)
{
	if (block == NULL)
		return (0);
	if (!block->next)
	{
		if (area->unset_size >= size - block->size)
		{
			area->unset_size -= size - block->size;
			init_block(block, size);
			return (1);
		}
		return (0);
	}
	else if (!block->next->busy)
		return (merge_existing_block(block, size, area->type));
	return (0);
}
