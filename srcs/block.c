/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/11 18:55:44 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static  void        init_block(t_block *block, size_t size) {
    block->size = size;
    block->busy = 1;
}

t_block             *check_free_block(t_block *first_block, size_t size) {
    
    t_block     *block;
    t_block     *new_block;
    int i;

    i = 0;
    block = first_block;
    if (block->busy == 0 && block->size >= size) {
        init_block(block, size);
        printf("first block of size %lu at adress : %p\n", size, block);
        return(block);
    }
    while (block->next) {
        printf("block n %d, at adress : %p\n", i, block);
        if (block->busy == 0 && block->size >= size) {
            init_block(block, size);
            return(block);
        }
        i++;
        block = block->next;
    }
    new_block = init_new_block(block, size);
    printf("new block n %d, of size %lu at adress : %p\n", i, size, new_block);
    block->next = new_block;
    return(new_block);
}

t_block             *init_new_block(t_block *prev, size_t size) {

    t_block *new_block;

    new_block = (t_block *)(&prev + prev->size + align_size(sizeof(t_block), 16));
    new_block->size = size;
    new_block->prev = prev;
    new_block->next = NULL;
    new_block->mem = &new_block + align_size(sizeof(t_block), 16);
    new_block->busy = 0;

    return(new_block);
}