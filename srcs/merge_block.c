/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:55:56 by isidibe-          #+#    #+#             */
/*   Updated: 2020/01/02 16:24:04 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int      merge_existing_block(t_block *block, size_t size, int type) {

    // t_block *rest;
    size_t  rest_size;

    // if (block->size + block->next->size + sizeof(block->next) >= size) {
    if (block->size + block->next->size + align_size(sizeof(t_block), 16) >= size) {
        rest_size = block->next->size + block->size + align_size(sizeof(t_block), 16) - size;
        ft_putendl("trying to merge block");
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
            lock_block(block->next);
        }
        block->size = rest_size + size;
        block->busy = 1;
        ft_putstr("got a rest of size ");
        ft_iprint(rest_size - align_size(sizeof(t_block), 16));
        ft_putendl("");
        // if (area->type < LARGE && block->size >= get_pool_size(area->type) + get_pool_size(area->type -1))
        create_intermediate_block(block, size, type);
        return(1);
    }
    ft_putendl("blocks not mergeable");
    return(0);
}

void        create_intermediate_block(t_block *block, size_t wanted_size, int type) {

    t_block *rest;
    size_t  rest_size;

    ft_putstr(CYAN "got a block of size ");
    ft_iprint(block->size);
    ft_putstr(" and a wanted size of ");
    ft_iprint(wanted_size);
    ft_putendl("");
    
    rest_size = block->size - wanted_size;

    ft_putstr("rest size ");
    ft_iprint(rest_size - align_size(sizeof(t_block), 16));
    ft_putendl("");

    if (block->size > wanted_size && rest_size > align_size(sizeof(t_block), 16)) {
        block->size = wanted_size;

        ft_putstr("creating intermediate block of size ");
        ft_iprint(rest_size - align_size(sizeof(t_block), 16));
        ft_putstr(", after block of size ");
        ft_iprint(block->size);
        ft_putendl("\n");

        rest = BLOCK_NEXT(block);

        rest->size = rest_size - align_size(sizeof(t_block), 16);
        rest->busy = 0;
        rest->prev = block;
        rest->next = block->next;
        if (rest->next) {
            rest->next->prev = rest;
            lock_block(rest->next);
        }
        ft_iprint(type);
        // rest = defragment_block(rest, type);
        block->next = rest;
        lock_block(rest);
    }
    else {
        ft_putendl("no rest");   
    }
}

int          check_mergeable_block(t_area *area, t_block *block, size_t size) {

    if (block == NULL) {
        ft_putendl(CYAN "block NULL !" END);
        return(0);
    }
    ft_putendl(CYAN "trying to find a way to extend block: merge/extend");
    if (!block->next) {
        ft_putendl("block as last block, extendable :");
        if (area->unset_size >= size - block->size) {
            area->unset_size -= size - block->size;
            init_block(block, size);
            ft_putendl("block extended" END);
            return(1);
        }
        ft_putendl("block not extendable, not enough space in area" END);
        return(0);
    }
    else if (!block->next->busy) {
        ft_putendl("block next exist and not busy, trying to merge it:");
        ft_putstr("size of next block : ");
        ft_iprint(block->next->size);
        ft_putendl("");
        return(merge_existing_block(block, size, area->type));
    }
    ft_putendl("not able to merge/extend block" END);
    return(0);
}