/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/12 16:30:15 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block             *check_free_block(t_area *area, size_t size)
{
    t_block *block;
    t_block *available_block;
    int     i;

    i = 0;
    available_block = NULL;
    block = area->first_block;
    while (block)
    {
        if (get_block_crc32(block) != block->crc32)
        {
            return(NULL);
        }
        if (block->busy == 0 && block->size >= size
            && (available_block == NULL || block->size < available_block->size))
        {
            available_block = block;
        }
        i++;
        if (!block->next)
            break;
        block = block->next;
    }
    if (available_block != NULL)
    {
        available_block->busy = 1;
        create_intermediate_block(available_block, size, area->type, 1);
        init_block(available_block, size);
        return(available_block);
    }

    if (area->unset_size < align_size(sizeof(t_block), 16) + size)
        return(NULL);
    block->next = append_new_block(block, size);
    lock_block(block);
    area->unset_size -= align_size(sizeof(t_block), 16) + block->next->size;
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size)
{
    t_block *new_block;

    new_block = BLOCK_NEXT(prev);
    new_block->size = size;
    new_block->prev = prev;
    new_block->next = NULL;
    new_block->busy = 1;
    lock_block(new_block);
    return(new_block);
}