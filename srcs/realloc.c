/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/04 15:27:56 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int          check_prev(t_block *block, size_t size) {
    if (block == NULL)
        return(0);
    if (block->prev != NULL && !block->prev->busy)
        if (block->prev->size + block->size >= size)
            return(1);
    return(0);
}

static void         *choose_alloction(t_area *area, t_block *block, size_t size) {

    size_t  original_size;
    void    *data;
    void    *new_ptr;

    original_size = block->size;
    data = BLOCK_MEM(block);
    if (block->size >= size)
        return(BLOCK_MEM(block));
    if (check_prev(block, size)) {
        printf("prev block of size %lu free an mergeable with the current one of size %lu\n", block->prev->size, block->size);
        block->busy = 0;
        block = block->prev;
    }
    if (check_mergeable_block(area, block, size)) {
        printf("block merged/extended from size %lu to size %lu\n", original_size, block->size);
        ft_memcpy(BLOCK_MEM(block), data, original_size);
        area->occupied += block->size - original_size;
        return(BLOCK_MEM(block));
    }
    else {
        printf("realloc: asking for new block\n");
        new_ptr = malloc(size);
        printf("new block of size %lu\n", size);
        ft_memcpy(new_ptr, data, original_size);
        return(new_ptr);
    }
}

void                *realloc(void *ptr, size_t size) {

    t_area  *area;
    t_block *block;

    if (ptr == NULL)
        return(malloc(size));
    else if (size == 0)
        ft_free(ptr);
    size = align_size(size, 16);
    printf("realloc: asked size : %lu\n", size);
    if ((area = retrieve_area(ptr)) == NULL)
        return(NULL);
    block = retrieve_block(area, ptr);
    printf("realloc: area and block found\n");
    return(choose_alloction(area, block, size));
}
