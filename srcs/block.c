/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/02 16:26:17 by isidibe-         ###   ########.fr       */
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
    while (block) {
        printf("block n %d, at adress : %p\n", i, block);
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
    printf("new block n %d, of size %lu at adress : %p\n", i, block->next->size, &block->next);
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size) {

    t_block *new_block;

    printf("append new block\n");
    // new_block = (t_block *)(&prev + align_size(sizeof(prev) + prev->size, 16));
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
    printf("NEW block at addr : %p\n", &new_block);
    printf("block size : %lu\n", new_block->size);
    printf("block busy : %d\n", new_block->busy);
    // printf("block : prev addr : %p\n", &new_block->prev);
    // printf("block : next addr : %p\n", &new_block->next);
    // new_block->mem = (void *)(&new_block + align_size(sizeof(t_block), 16));
    // printf("mem addr : %p, size of block : %lu\n", new_block->mem, sizeof(new_block));
    printf("mem : %x\n", &new_block + align_size(sizeof(t_block), 16));
}