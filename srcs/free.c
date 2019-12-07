/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/07 13:55:52 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

void            free(void *ptr) {
    
    t_block *block;
    t_area  *area;

    ft_putendl(RED "==== FREE ====");
    if (ptr == NULL) {
        ft_putendl("ptr NULL" END);
        return ;
    }
    // printf("FREE pointer not null\n");
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
    if (block == NULL) {
        ft_putendl("block NULL");
        return ;
    }
    ft_putstr("freeing block of size ");
    ft_iprint(block->size);
    ft_putendl("");
    block->busy = 0;
    // printf("FREE pointer freed, block size %lu\n", block->size);
    // printf("occupied size of area before clean : %lu/%lu\n", area->occupied, area->size);
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
    // printf("occupied size of area after clean : %lu/%lu\n", area->occupied, area->size);
    if (area->full)
        area->full = 0;
    if (area->occupied == 0) {
        // printf("FREE free area of type %d\n", area->type);
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
        // printf("first allocation of type %d is empty and freed\n", area->type);
        g_type[area->type].first_area = next_area;
    }
    else if (next_area == NULL && prev_area == NULL) {
        ft_putstr("allocation of type ");
        ft_iprint(area->type);
        ft_putendl(" is empty");
        // printf("allocation of type %d is empty\n", area->type);
        g_type[area->type].first_area = NULL;
    }
    munmap((void *)area, area->size);
}