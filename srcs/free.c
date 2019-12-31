/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/31 11:56:31 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>



static t_block    *defragment_block(t_block *block, int type) {
    
    t_block *tmp;

    if (block->next && !block->next->busy) {
        tmp = block->next;
        block->next = tmp->next;
        if (tmp->next) {
            tmp->next->prev = block;
            lock_block(tmp->next);
        }
        block->size += tmp->size + sizeof(t_block);
    }
    if (block->prev && !block->prev->busy) {
        tmp = block;
        block = block->prev;
        block->next = tmp->next;
        if (tmp->next) {
            tmp->next->prev = block;
            lock_block(block->next);
        }
        block->size += tmp->size + sizeof(t_block);
    }
    if (type < LARGE && block->size >= get_pool_size(type) + get_pool_size(type -1)) {
        create_intermediate_block(block, get_pool_size(type));
        if (block->next && block->next->size >= get_pool_size(type) + get_pool_size(type -1)) {
            create_intermediate_block(block->next, get_pool_size(type));
            lock_block(block->next);
        }
    }
    return(block);
}


void            free(void *ptr) {
    
    t_block *block;
    t_area  *area;

    ft_putendl(RED "==== FREE ====");
    if (ptr == NULL) {
        ft_putendl("ptr NULL" END);
        return ;
    }
    ft_putendl("get area :" END);
    area = retrieve_area(ptr);
    ft_putendl(RED "get block :" END);
    block = retrieve_block(area, ptr);
    if (area && block) {
        ft_putendl(RED "got area and block, freeing :");
        free_block(area, block);
    }
    else
        ft_putendl(RED "no block found" END);
}


void    free_block(t_area *area, t_block *block) {
    if (block == NULL || block->busy == 0) {
        ft_putendl("block NULL");
        return ;
    }
    ft_putstr("freeing block of size ");
    ft_iprint(block->size);
    ft_putendl("");
    ft_putstr("occupied size of area before clean : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
    area->occupied -= sizeof(t_block) + block->size;
    ft_putstr("occupied size of area after clean : ");
    ft_iprint(area->occupied);
    ft_putstr("/");
    ft_iprint(area->size);
    ft_putendl("");
    block->busy = 0;
    ft_putstr("defrangmanting block with size : ");
    ft_iprint(block->size);
    ft_putendl("");
    block = defragment_block(block, area->type);
    ft_putstr(RED "defrangmented block of size : ");
    ft_iprint(block->size);
    ft_putendl("");
    lock_block(block);
    if (area->full)
        area->full = 0;
    if (area->occupied == 0) {
        show_alloc_mem();
        ft_putstr("freeing area of type ");
        ft_iprint(area->type);
        ft_putendl("");
        free_area(area);
    }
}

void    free_area(t_area *area) {
    
    t_area *prev_area;
    t_area *next_area;

    next_area = area->next;
    prev_area = area->prev;
    if (next_area)
        next_area->prev = prev_area;
    if (prev_area)
        prev_area->next = next_area;
    if (next_area && prev_area == NULL) {
        ft_putstr("first allocation of type ");
        ft_iprint(area->type);
        ft_putendl(" is empty and freed, link global to the next one");
        g_type[area->type].first_area = next_area;
    }
    else if (next_area == NULL && prev_area == NULL) {
        ft_putstr("allocation of type ");
        ft_iprint(area->type);
        ft_putendl(" is empty");
        g_type[area->type].first_area = NULL;
    }
    munmap((void *)area, area->size);
}