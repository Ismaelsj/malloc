/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/07 16:41:43 by isidibe-         ###   ########.fr       */
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

static void         *up_sizing_block(t_area *area, t_block *block, size_t size) {

    size_t  original_size;
    void    *data;
    void    *new_ptr;

    original_size = block->size;
    data = BLOCK_MEM(block);
    if (block->size >= size)
        return(BLOCK_MEM(block));
    if (check_prev(block, size)) {
        ft_putstr("prev block of size ");
        ft_iprint(block->prev->size);
        ft_putstr(", free an mergeable with the current one of size ");
        ft_iprint(block->size);
        ft_putendl("");
        // printf("prev block of size %lu free an mergeable with the current one of size %lu\n", block->prev->size, block->size);
        block->busy = 0;
        block = block->prev;
    }
    ft_putstr(END);
    if (check_mergeable_block(area, block, size)) {
        ft_putstr(YELLOW "block merged/extended from size ");
        ft_iprint(original_size);
        ft_putstr(" to size ");
        ft_iprint(block->size);
        ft_putendl("");
        // printf("block merged/extended from size %lu to size %lu\n", original_size, block->size);
        ft_memcpy(BLOCK_MEM(block), data, original_size);
        area->occupied += block->size - original_size;
        ft_putendl("returning merged/extended block" END);
        return(BLOCK_MEM(block));
    }
    else {
        // printf("realloc: asking for new block\n");
        ft_putendl(YELLOW "new block needed, calling malloc:" END);
        new_ptr = malloc(size);
        ft_putendl(YELLOW "got new block of size ");
        ft_iprint(size);
        ft_putendl("");
        ft_putendl(YELLOW "now copy mem");
        // printf("new block of size %lu\n", size);
        ft_memcpy(new_ptr, data, original_size);
        ft_putendl("memory copied, freeing old one" END);
        free(BLOCK_MEM(block));
        ft_putendl("return mem" END);
        return(new_ptr);
    }
}

static void         *down_sizing_block(t_area *area, t_block *block, size_t size) {
    
    size_t  original_size;
    t_block *rest;
    void    *data;

    original_size = block->size;
    data = BLOCK_MEM(block);
    block->size = size;
    ft_putstr("block down sized from ");
    ft_iprint(original_size);
    ft_putstr(" to size ");
    ft_iprint(block->size);
    ft_putendl("");
    // printf("block down sized from %lu to %lu\n", original_size, block->size);
    if (original_size - size > sizeof(t_block)) {
        rest = BLOCK_NEXT(block);
        rest->size = original_size - size - sizeof(rest);
        rest->busy = 0;
        rest->prev = block;
        rest->next = block->next;
        if (rest->next)
            rest->next->prev = rest;
        block->next = rest;
        ft_putstr("got rest of size ");
        ft_iprint(rest->size);
        ft_putendl("");
        // printf("got rest of size %lu\n", rest->size);
    }
    ft_memcpy(BLOCK_MEM(block), data, size);
    area->occupied -= original_size - size;
    ft_putendl("returning mem" END);
    return(BLOCK_MEM(block));
}

void                *realloc(void *ptr, size_t size) {

    t_area  *area;
    t_block *block;
    size_t  aligned_size;

    ft_putendl(YELLOW "==== REALLOC ====");
    if (ptr == NULL) {
        ft_putendl("ptr NULL, allocate new mem with malloc :" END);
        return(malloc(size));
    }
    else if (size == 0) {
        ft_putendl("size = 0, freeing ptr" END);
        free(ptr);
        return(NULL);
    }
    aligned_size = align_size(size, 16);
    ft_putstr("asked size : ");
    ft_iprint(aligned_size);
    ft_putendl("" END);
    // printf("realloc: asked aligned_size : %lu\n", aligned_size);
    if ((area = retrieve_area(ptr)) == NULL)
        return(NULL);
    ft_putendl(YELLOW "trying to find block" END);
    block = retrieve_block(area, ptr);
    ft_putendl(YELLOW "block found");
    if (choose_pool(aligned_size) != area->type)
        return(malloc(size));
    // printf("realloc: area and block found\n");
    if (aligned_size < block->size) {
        ft_putendl("trying to down size block :");
        return(down_sizing_block(area, block, aligned_size));
    }
    ft_putendl("trying to up size block :");
    return(up_sizing_block(area, block, aligned_size));
}
