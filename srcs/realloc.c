/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:15:46 by isidibe-          #+#    #+#             */
/*   Updated: 2020/01/03 15:53:13 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// line norme ok
static int          check_prev(t_block *block, size_t size)
{
    if (block == NULL)
        return(0);
    if (block->prev != NULL && !block->prev->busy)
        if (block->prev->size + block->size >= size)
            return(1);
    return(0);
}

static void         *up_sizing_block(t_area *area, t_block *block, size_t size)
{
    size_t  original_size;
    void    *data;
    t_block    *new_block;

    original_size = block->size;
    data = BLOCK_MEM(block);
    if (block->size >= size) {
        pthread_mutex_unlock(&g_mutex);
        return(BLOCK_MEM(block));
    }
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
        pthread_mutex_unlock(&g_mutex);
        return(BLOCK_MEM(block));
    }
    else {
        ft_putendl(YELLOW "new block needed, calling malloc:" END);
        if ((new_block = check_free_area(choose_pool(size), size)) == NULL) {
            pthread_mutex_unlock(&g_mutex);
            return(NULL);
        }
        ft_putstr(YELLOW "got new block of size ");
        ft_iprint(size);
        ft_putendl("");
        ft_putstr("occupied size of area after realloc : ");
        ft_iprint(area->occupied);
        ft_putstr("/");
        ft_iprint(area->size);
        ft_putendl("");
        ft_putendl(YELLOW "now copy mem");
        ft_memcpy(BLOCK_MEM(new_block), data, original_size);
        ft_putendl("memory copied, freeing old one" END);
        pthread_mutex_unlock(&g_mutex);
        free_block(area, block);
        ft_putendl(YELLOW"return mem" END);
        return(BLOCK_MEM(new_block));
    }
}

// line norme ok
static void         *down_sizing_block(t_area *area, t_block *block,\
                                        size_t size)
{
    size_t  original_size;
    // t_block *rest;
    void    *data;

    original_size = block->size;
    data = BLOCK_MEM(block);
    ft_putstr("block down sized from ");
    ft_iprint(original_size);
    ft_putstr(" to size ");
    ft_iprint(size);
    ft_putendl("");
    create_intermediate_block(block, size, area->type, 1);
    ft_memcpy(BLOCK_MEM(block), data, size);
    lock_block(block);
    area->occupied -= original_size - block->size;
    ft_putendl("returning mem" END);
    ft_putstr("occupied size of area after realloc : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
    pthread_mutex_unlock(&g_mutex);
    return(BLOCK_MEM(block));
}

void                *realloc(void *ptr, size_t size)
{
    t_area  *area;
    t_block *block;
    size_t  aligned_size;

    ft_putendl(YELLOW "==== REALLOC ====");
    if (ptr == NULL)
    {
        ft_putendl("ptr NULL, allocate new mem with malloc :" END);
        return(malloc(size));
    }
    else if (size == 0)
    {
        ft_putendl("size = 0" END);
        if (!ptr)
            return(NULL);
        free(ptr);
        return(malloc(16));
    }
    aligned_size = align_size(size, 16);
    ft_putstr("asked size : ");
    ft_iprint(aligned_size);
    ft_putendl("" END);
    pthread_mutex_lock(&g_mutex);
    if ((area = retrieve_area(ptr)) == NULL)
    {
        ft_putendl("area not found, get new allocation");
        pthread_mutex_unlock(&g_mutex);
        return(malloc(size));
    }
    ft_putendl(YELLOW "trying to find block" END);
    block = retrieve_block(area, ptr);
    if (block->busy == 0)
    {
        pthread_mutex_unlock(&g_mutex);
        return(malloc(size));
    }
    ft_putendl(YELLOW "block found");
    if (choose_pool(aligned_size) != area->type)
    {
        ft_putstr("asked size not in ");
        ft_iprint(area->type);
        ft_putstr(" type, freeing block and creating new one in area of type ");
        ft_iprint(choose_pool(aligned_size));
        ft_putendl(""RED);
        pthread_mutex_unlock(&g_mutex);
        free_block(area, block);
        ft_putstr(""END);
        return(malloc(size));
    }
    ft_putstr("occupied size of area before realloc : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
    if (aligned_size < block->size)
    {
        if (area->type == LARGE)
        {
            ft_putendl("freeing large block and creating new one");
            pthread_mutex_unlock(&g_mutex);
            free_block(area, block);
            return(malloc(size));
        }
        ft_putendl("trying to down size block :");
        return(down_sizing_block(area, block, aligned_size));
    }
    ft_putendl("trying to up size block :");
    return(up_sizing_block(area, block, aligned_size));
}
