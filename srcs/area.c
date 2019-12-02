/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/02 15:10:37 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *check_free_area(int type, size_t size) {
    
    t_area  *area;
    t_block *block;
    int     i;
    
    i = 0;
    if (g_type[type].first_area == NULL) {
        printf("create first area of type %d\n", type);
        g_type[type] = new_heap(type, size);
    }
    area = g_type[type].first_area;
    if (area->full == 0 && area->occupied + (sizeof(t_block) + size) <= area->size) {
        printf("========= occupied area : %lu, %lu =========\n", area->occupied, sizeof(t_block) + size);
        printf("first area at adress : %p\ndiff addr : %p %p\n", &area, &area, &area->first_block);
        block = check_free_block(area, size);
        printf("area size before adding block : %lu\n", area->occupied);
        printf("add block of size : %lu and size of block : %lu\n", size, sizeof(block));
        area->occupied += sizeof(block) + size;
        printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
        if (type == LARGE)
            area->full = 1;
        return(block);
        // return(check_area_limit(area, size, type));
    }
    while (area->next) {
        printf("area n %d, adress : %p\n", i, area);
        if (area->full == 0 + (sizeof(t_block) + size) <= area->size) {
            block = check_free_block(area, size);
            printf("add block of size : %lu and size of block : %lu\n", size, sizeof(block));
            area->occupied += sizeof(block) + size;
            printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
            if (type == LARGE)
                area->full = 1;
            return(block);
            // return(check_free_block(area, size));
            // return(check_area_limit(area, size, type));
        }
        i++;
        area = area->next;
    }
    // if ((area->next = request_memory(area, get_page_size(type, size))) == NULL)
    //     return(NULL);
    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, size, type);
    printf("new area n %d of type %d, adress : %p\n", i, type, area->next);
    block = check_free_block(area, size);
    printf("add block of size : %lu and size of block : %lu\n", size, sizeof(block));
    area->occupied += sizeof(block) + size;
    printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
    if (type == LARGE)
        area->full = 1;
    return(block);
    // return(check_free_block(area, size));
    // return(check_area_limit(area, size, type));
}

t_block     *append_new_area(t_area *area, size_t size) {

    t_block *new_block;

    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(area->type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, size, area->type);
    area = area->next;
    printf("append new area of size %lu\n", area->size);
    new_block = check_free_block(area, size);
    printf("add block of size : %lu and size of block : %lu\n", size, sizeof(new_block));
    area->occupied += sizeof(new_block) + size;
    printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
    return(new_block);
}

void        init_area(t_area *area, t_area *prev, size_t size, int type) {
    // area->first_block = (t_block *)&area + align_size(sizeof(t_area), 16);
    area->first_block = (t_block *)AREA_MEM(area);
    area->size = get_page_size(type, size);
    area->type = type;
    area->occupied = 0;
    area->full = 0;
    area->prev = prev;
    area->next = NULL;
    printf("area at addr : %p\n", &area);
    printf("area size : %lu\n", area->size);
    printf("area type : %d\n", area->type);
    printf("area occupied : %lu\n", area->occupied);
    printf("area full : %d\n", area->full);
    init_new_block(area->first_block, size);
    // area->first_block->prev = NULL;
}

t_area      *request_memory(t_area *prev, size_t size) {
    
    t_area *new_alloc;

    if ((new_alloc = mmap(prev, size, PROT_READ|PROT_WRITE|PROT_EXEC,\
        MAP_ANON|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return(NULL);
    return(new_alloc);
}