/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/24 20:25:17 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *check_free_area(int type, size_t size) {
    
    t_area  *area;
    int     i;
    
    i = 0;
    if (g_type[type].first_area == NULL) {
        printf("create first area\n");
        g_type[type] = new_heap(type, size);
    }
    area = g_type[type].first_area;
    if (area->full == 0){
        printf("first area at adress : %p\ndiff addr : %p %p\n", &area, &area, &area->first_block);
        return(check_free_block(area, size));
        // return(check_area_limit(area, size, type));
    }
    while (area->next) {
        printf("area n %d, adress : %p\n", i, area);
        if (area->full == 0) {
            return(check_free_block(area, size));
            // return(check_area_limit(area, size, type));
        }
        i++;
        area = area->next;
    }
    // if ((area->next = request_memory(area, get_page_size(type, size))) == NULL)
    //     return(NULL);
    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, get_page_size(type, size));
    printf("new area n %d, adress : %p\n", i, area->next);
    return(check_free_block(area, size));
    // return(check_area_limit(area, size, type));
}

t_block     *append_new_area(t_area *area, size_t size) {
    t_block *new_block;

    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(area->type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, get_page_size(area->type, size));
    new_block = check_free_block(area, size);
    area->occupied += sizeof(new_block) + size;
    return(new_block);
}

void        init_area(t_area *area, t_area *prev, size_t size) {
    // area->first_block = (t_block *)&area + align_size(sizeof(t_area), 16);
    area->first_block = (t_block *)AREA_MEM(area);
    printf("area : block addr : %p\n", &area->first_block);
    printf("area : size  addr : %p\n", &area->size);
    printf("area : full  addr : %p\n", &area->full);
    printf("area : prev  addr : %p\n", &area->prev);
    printf("area : next  addr : %p\n", &area->next);
    area->size = size;
    area->occupied = 0;
    area->full = 0;
    area->prev = prev;
    area->next = NULL;
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