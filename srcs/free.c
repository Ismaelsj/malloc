/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/04 10:41:37 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

void            ft_free(void *ptr) {
    
    t_block *block;
    t_area  *area;

    if (ptr == NULL)
        return ;
    printf("FREE pointer not null\n");
    area = retrieve_area(ptr);
    block = retrieve_block(area, ptr);
    free_block(area, block);
}

void    free_block(t_area *area, t_block *block) {
    if (block == NULL)
        return ;
    block->busy = 0;
    printf("FREE pointer freed, block size %lu\n", block->size);
    printf("occupied size of area before clean : %lu/%lu\n", area->occupied, area->size);
    area->occupied -= sizeof(block) + block->size;
    printf("occupied size of area after clean : %lu/%lu\n", area->occupied, area->size);
    if (area->full)
        area->full = 0;
    if (area->occupied == 0) {
        printf("FREE free area of type %d\n", area->type);
        free_area(area);
    }
}

void    free_area(t_area *area) {
    
    t_area *prev_area;
    t_area *next_area;

    next_area = area->next;
    prev_area = area->prev;
    if (next_area != NULL)
        next_area->prev = prev_area;
    if (prev_area != NULL)
        prev_area->next = next_area;
    if (next_area != NULL && prev_area == NULL) {
        printf("first allocation of type %d is empty and freed\n", area->type);
        g_type[area->type].first_area = next_area;
    }
    else if (next_area == NULL && prev_area == NULL) {
        printf("allocation of type %d is empty\n", area->type);
        g_type[area->type].first_area = NULL;
    }
    munmap((void *)area, area->size);
}