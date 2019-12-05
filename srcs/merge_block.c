/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:55:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/05 17:55:06 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int      merge_existing_block(t_block *block, size_t size) {

    t_block *rest;
    size_t  rest_size;

    if (block->size + block->next->size >= size) {
        rest_size = block->next->size + block->size - size;
        // printf("try to merge block of size %lu and %lu, for size %lu, with a rest of %lu\n", block->size, block->next->size, size, rest_size);
        ft_putendl("trying to merge block");
        // rest = block->next;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
        // block->next = rest->next;
        // block->next->prev = block;
        block->size = size;
        block->busy = 1;
        ft_putstr("got a rest of ");
        ft_iprint(rest_size);
        ft_putendl("");
        // printf("new merged block of size %lu\n", block->size);
        if (rest_size > sizeof(block)) {
            ft_putendl("got rest, creating intermediate block");
            rest = BLOCK_NEXT(block);
            rest->size = rest_size;
            rest->busy = 0;
            rest->prev = block;
            rest->next = block->next;
            if (rest->next)
                rest->next->prev = rest;
            block->next = rest;
            // printf("rest : block of size %lu\n", rest->size);
            ft_putendl("intermediate block created end linked" END);
        }
        else
            ft_putendl("no rest" END);
        return(1);
    }
    ft_putendl("blocks not mergeable");
    // printf("blocks of size %lu and %lu not mergeable for size %lu\n", block->size, block->next->size, size);
    return(0);
}

// void        create_intermediate_block(t_block *block, size_t wanted_size) {
    
//     t_block *rest;
//     size_t  rest_size;

//     if (block->size - wanted_size > sizeof(block)) {
//         rest_size = 
//         rest = BLOCK_NEXT(block);
//         rest->size = wanted_size - sizeof(block);
//         rest->busy = 0;
//         rest->prev = block;
//         rest->next = block->next;
//         if (rest->next)
//             rest->next->prev = rest;
//         block->next = rest;
//     }
// }

int          check_mergeable_block(t_area *area, t_block *block, size_t size) {

    if (block == NULL) {
        ft_putendl(CYAN "block NULL !" END);
        return(0);
    }
    ft_putendl(CYAN "trying to find a way to extend block: merge/extend");
    if (!block->next) {
        // printf("try extend block of size %lu, area unset size : %lu\n", block->size, area->unset_size);
        ft_putendl("block as last block, extendable :");
        if (area->unset_size >= size) {
            area->unset_size -= size - block->size;
            init_block(block, size);
            ft_putendl("block extended" END);
            // printf("block extended to size %lu, area unset size : %lu\n", block->size, area->unset_size);
            return(1);
        }
        ft_putendl("block not extendable, not enough space in area" END);
        return(0);
    }
    else if (!block->next->busy) {
        ft_putendl("block next exist and not busy, trying to merge it:");
        return(merge_existing_block(block, size));
    }
    // printf("next block not free\n");
    ft_putendl("not able to merge/extend block" END);
    return(0);
}