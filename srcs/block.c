/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/02 16:47:10 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static  void        init_block(t_block *block, size_t size) {
    block->size = size;
    block->busy = 1;
}

t_block             *check_free_block(t_area *area, size_t size) {
    
    t_block     *block;
    int i;

    i = 0;
    block = area->first_block;
    printf("loop over blocks :\n");
    while (block) {
        printf("    block n %d of size %lu, busy %d\n", i, block->size, block->busy);
        if (block->busy == 0 && block->size >= size) {
            init_block(block, size);
            return(block);
        }
        i++;
        if (!block->next) 
            break;
        block = block->next;
    }
    block->next = append_new_block(block, size);
    printf(BLUE "new block n %d, of size %lu" END "\n", i, block->next->size);
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size) {

    t_block *new_block;

    printf("append new block\n");
    new_block = BLOCK_NEXT(prev);
    new_block->size = size;
    new_block->prev = prev;
    new_block->next = NULL;
    new_block->busy = 1;

    return(new_block);
}

void            init_new_block(t_block *new_block, size_t size) {

    new_block->size = size;
    new_block->busy = 0;
    new_block->prev = NULL;
    new_block->next = NULL;
    printf(BLUE "new block of size %lu" END "\n", new_block->size);
    // printf("block size : %lu\n", new_block->size);
    // printf("block busy : %d\n", new_block->busy);
    // printf("mem : %x\n", &new_block + align_size(sizeof(t_block), 16));
}