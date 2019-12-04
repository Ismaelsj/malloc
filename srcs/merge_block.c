/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:55:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/04 15:22:26 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int      merge_existing_block(t_block *block, size_t size) {

    t_block *rest;
    size_t  rest_size;

    if (block->size + block->next->size >= size) {
        rest_size = block->next->size + block->size - size;
        printf("try to merge block of size %lu and %lu, for size %lu, with a rest of %lu\n", block->size, block->next->size, size, rest_size);
        block->next = block->next->next;
        block->next->prev = block;
        block->size = size;
        block->busy = 1;
        printf("new merged block of size %lu\n", block->size);
        if (rest_size > 0) {
            rest = BLOCK_NEXT(block);
            rest->size = rest_size;
            rest->busy = 0;
            rest->prev = block;
            rest->next = block->next;
            if (rest->next)
                rest->next->prev = rest;
            block->next = rest;
            printf("rest : block of size %lu\n", rest->size);
        }
        return(1);
    }
    printf("blocks of size %lu and %lu not mergeable for size %lu\n", block->size, block->next->size, size);
    return(0);
}

int          check_mergeable_block(t_area *area, t_block *block, size_t size) {

    if (block == NULL)
        return(0);
    if (!block->next) {
        printf("try extend block of size %lu, area unset size : %lu\n", block->size, area->unset_size);
        if (area->unset_size >= size) {
            area->unset_size -= size - block->size;
            init_block(block, size);
            printf("block extended to size %lu, area unset size : %lu\n", block->size, area->unset_size);
            return(1);
        }
        return(0);
    }
    else if (!block->next->busy)
        return(merge_existing_block(block, size));
    printf("next block not free\n");
    return(0);
}