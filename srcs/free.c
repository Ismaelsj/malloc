/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/02 14:44:34 by isidibe-         ###   ########.fr       */
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
    area = get_area(ptr);
    if (area == NULL) {
        printf("area not found\n");
        return ;
    }
    block = area->first_block;
    while (block) {
        if (BLOCK_MEM(block) == ptr)
            break;
        block = block->next;
    }
    block->busy = 0;
    printf("FREE pointer freed\n");
    printf("occupied size of area before clean : %lu/%lu\n", area->occupied, area->size);
    area->occupied -= sizeof(block) + block->size;
    printf("occupied size of area after clean : %lu/%lu\n", area->occupied, area->size);
    if (area->full)
        area->full = 0;
    if (area->occupied == 0) {
        printf("FREE free area of type %d\n", area->type);
        free_area(area);
    }
    // check_free_alloc(block, block->size);
}

t_area  *get_area(void *ptr) {

    t_area  *area;
    t_block *block;
    int     type;
    int     i;
    int     j;

    type = 0;
    i = 0;
    j = 0;
    while (type <= LARGE) {
        printf("searching in area of type %d\n", type);
        area = g_type[type].first_area;
        i = 0;
        while (area) {
            printf("searching in area n %d\n", i);
            block = area->first_block;
            j = 0;
            while (block) {
                printf("searching for block n %d\n", j);
                if (BLOCK_MEM(block) == ptr) {
                    printf("blockn n %d, found in area n %d, of type %d\n", j, i, type);
                    return(area);
                }
                block = block->next;
                j++;
            }
            area = area->next;
            i++;
        }
        type++;
    }
    return(NULL);
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