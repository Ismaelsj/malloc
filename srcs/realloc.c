/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/30 15:34:51 by isidibe-         ###   ########.fr       */
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
        block->busy = 0;
        block = block->prev;
        block->busy = 1;
    }
    ft_putstr(END);
    if (check_mergeable_block(area, block, size)) {
        ft_putstr(YELLOW "block merged/extended from size ");
        ft_iprint(original_size);
        ft_putstr(" to size ");
        ft_iprint(block->size);
        ft_putendl("");
        ft_memcpy(BLOCK_MEM(block), data, original_size);
        lock_block(block);
        area->occupied += block->size - original_size;
        ft_putendl("returning merged/extended block" END);
        ft_putstr("occupied size of area after realloc : ");
        ft_iprint(area->occupied);
        ft_putstr("/");
        ft_iprint(area->size);
        ft_putendl("");
        return(BLOCK_MEM(block));
    }
    else {
        ft_putendl(YELLOW "new block needed, calling malloc:" END);
        if ((new_ptr = malloc(size)) == NULL)
            return(NULL);
        ft_putendl(YELLOW "got new block of size ");
        ft_iprint(size);
        ft_putendl("");
        ft_putstr("occupied size of area after realloc : ");
        ft_iprint(area->occupied);
        ft_putstr("/");
        ft_iprint(area->size);
        ft_putendl("");
        ft_putendl(YELLOW "now copy mem");
        ft_memcpy(new_ptr, data, original_size);
        ft_putendl("memory copied, freeing old one" END);
        // free(BLOCK_MEM(block));
        free_block(area, block);
        ft_putendl(YELLOW"return mem" END);
        return(new_ptr);
    }
}

static void         *down_sizing_block(t_area *area, t_block *block, size_t size) {
    
    size_t  original_size;
    // t_block *rest;
    void    *data;

    original_size = block->size;
    data = BLOCK_MEM(block);
    // block->size = size;
    ft_putstr("block down sized from ");
    ft_iprint(original_size);
    ft_putstr(" to size ");
    ft_iprint(size);
    ft_putendl("");
    // printf("block down sized from %lu to %lu\n", original_size, block->size);
    create_intermediate_block(block, size);
    ft_memcpy(BLOCK_MEM(block), data, size);
    lock_block(block);
    area->occupied -= original_size - block->size;
    ft_putendl("returning mem" END);
    ft_putstr("occupied size of area after realloc : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
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
        ft_putendl("size = 0" END);
        if (!ptr)
            return(NULL);
        free(ptr);
        return(malloc(size));
    }
    aligned_size = align_size(size, 16);
    ft_putstr("asked size : ");
    ft_iprint(aligned_size);
    ft_putendl("" END);
    // printf("realloc: asked aligned_size : %lu\n", aligned_size);
    if ((area = retrieve_area(ptr)) == NULL) {
        ft_putendl("area not found, get new allocation");
        return(malloc(size));
    }
        // return(NULL);
    ft_putendl(YELLOW "trying to find block" END);
    block = retrieve_block(area, ptr);
    if (block->busy == 0)
        return(malloc(size));
    ft_putendl(YELLOW "block found");
    if (choose_pool(aligned_size) != area->type) {
        ft_putstr("asked size not in ");
        ft_iprint(area->type);
        ft_putstr(" type, freeing block and creating new one in area of type ");
        ft_iprint(choose_pool(aligned_size));
        ft_putendl(""RED);
        free_block(area, block);
        ft_putstr(""END);
        return(malloc(size));
    }
    // printf("realloc: area and block found\n");
    ft_putstr("occupied size of area before realloc : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
    if (aligned_size < block->size) {
        ft_putendl("trying to down size block :");
        return(down_sizing_block(area, block, aligned_size));
    }
    ft_putendl("trying to up size block :");
    return(up_sizing_block(area, block, aligned_size));
}
