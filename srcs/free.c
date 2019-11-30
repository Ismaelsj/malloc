/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:44:09 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/30 14:44:58 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

void            ft_free(void *ptr) {
    
    t_block *block;

    if (ptr == NULL)
        return ;
    printf("FREE pointer not null\n");
    block = (void *)(ptr - sizeof(t_block));
    block->busy = 0;
    printf("FREE pointer freed\n");
    check_free_alloc(block, block->size);
}

void    check_free_alloc(t_block *block, size_t size) {

    t_area *area;

    while (block->prev != NULL)
        block = block->prev;
    printf("retrieve area\n");
    area = (t_area *)(&block - sizeof(t_area));
    if ((area = get_area(block)) == NULL)
        return ;
    printf("size of area before clean : %lu\n", area->occupied);
    area->occupied -= sizeof(block) + size;
    printf("size of area after clean : %lu\n", area->occupied);
    if (area->full)
        area->full = 0;
    if (area->occupied == 0) {
        printf("FREE free area\n");
        free_area(area);
    }
}

t_area  *get_area(t_block *first_block) {

    size_t  type;
    t_area  *area;

    type = 0;
    while (type <= LARGE) {
        area = g_type[type].first_area;
        printf("first block : %p\n", AREA_MEM(area));
        printf("block : %p\n", first_block);
        if (AREA_MEM(area) == first_block) {
            printf("FREE area found\n");
            return(area);
        }
        type++;
    }
    printf("FREE area not found ! \n");
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
    munmap((void *)area, area->size);
}