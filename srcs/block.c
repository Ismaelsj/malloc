/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/01 16:45:01 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static  void        init_block(t_block *block, size_t size) {
    block->size = size;
    block->busy = 1;
}

t_block             *check_free_block(t_area *area, size_t size) {
    
    t_block     *block;
    t_block     *new_block;
    int i;

    i = 0;
    // block = first_block;
    block = area->first_block;
    if (block->busy == 0 && block->size >= size) {
        init_block(block, size);
        area->occupied += sizeof(block) + size;
        printf("first block of size %lu at adress : %p\n", size, &block);
        return(block);
    }
    while (block->next) {
        printf("block n %d, at adress : %p\n", i, block);
        if (block->busy == 0 && block->size >= size) {
            init_block(block, size);
            area->occupied += sizeof(block) + size;
            return(block);
        }
        i++;
        block = block->next;
    }
    new_block = check_area_limit(area, block, size);
    printf("new block n %d, of size %lu at adress : %p\n", i, new_block->size, &new_block);
    // block->next = new_block;
    return(new_block);
}

t_block     *check_area_limit(t_area *area, t_block *block, size_t size) {
    
    t_block *new_block;

    if (area->occupied + (sizeof(t_block) + size) > area->size) {
        printf("area full : %lu, %lu, %lu, area size : %lu\n", area->occupied, sizeof(t_block), size, area->size);
        // area->full = 1;
        return(append_new_area(area, size));
    }
    else {
        new_block = append_new_block(block, size);
        area->occupied += sizeof(new_block) + size;
        block->next = new_block;
        return(new_block);
    }
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

    printf("block addr : %p\n", &new_block);
    printf("block : size addr : %p\n", &new_block->size);
    printf("block : busy addr : %p\n", &new_block->busy);
    // printf("block : mem  addr : %p\n", &new_block->mem);
    printf("block : prev addr : %p\n", &new_block->prev);
    printf("block : next addr : %p\n", &new_block->next);
    new_block->size = size;
    new_block->busy = 0;
    new_block->prev = NULL;
    new_block->next = NULL;
    // new_block->mem = (void *)(&new_block + align_size(sizeof(t_block), 16));
    // printf("mem addr : %p, size of block : %lu\n", new_block->mem, sizeof(new_block));
    printf("mem : %x\n", &new_block + align_size(sizeof(t_block), 16));
}