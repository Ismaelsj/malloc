/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/16 14:08:25 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *check_free_area(int type, size_t size) {
    
    t_area  *area;
    int i;
    
    i = 0;
    if (g_type[type].first_area == NULL) {
        printf("create first area\n");
        g_type[type] = new_heap(type, size);
    }
    area = g_type[type].first_area;
    if (area->full == 0){
        printf("first area at adress : %p\ndiff addr : %p %p\n", &area, &area, &area->first_block);
        return(check_free_block(area->first_block, size));
    }
    while (area->next) {
        printf("area n %d, adress : %p\n", i, area);
        if (area->full == 0)
            return(check_free_block(area->first_block, size));
        i++;
        area = area->next;
    }
    if ((area->next = request_memory(area, get_page_size(type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, get_page_size(type, size));
    printf("new area n %d, adress : %p\n", i, area->next);
    return(check_free_block(area->first_block, size));
}

void        init_area(t_area *area, t_area *prev, size_t size) {
    area->first_block = (t_block *)&area + align_size(sizeof(t_area), 16);
    printf("area : block addr : %p\n", &area->first_block);
    printf("area : size  addr : %p\n", &area->size);
    printf("area : full  addr : %p\n", &area->full);
    printf("area : prev  addr : %p\n", &area->prev);
    printf("area : next  addr : %p\n", &area->next);
    area->size = size;
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