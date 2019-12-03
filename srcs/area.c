/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/03 15:33:43 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int  get_nb_block(int type) {
    if (type == TINY | type == SMALL)
        return(NB_BLOCKS);
    else
        return(1);
}

t_block     *check_free_area(int type, size_t size) {
    
    t_area  *area;
    int     i;
    
    i = 0;
    if (g_type[type].first_area == NULL) {
        printf(GREEN "create first area of type %d" END "\n", type);
        g_type[type] = new_heap(type, size);
    }
    area = g_type[type].first_area;
    printf("loop over areas :\n");
    while (area) {
        printf("    area n %d: occupied/size : %lu/%lu, full %d, unset size : %lu\n", i, area->occupied, area->size, area->full, area->unset_size);
        if (area->occupied + (sizeof(t_block) + size) <= area->size)
            return(get_block(area, size));
        i++;
        if (!area->next)
            break;
        area = area->next;
    }
    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(type, size))) == NULL)
        return(NULL);
    init_area(area->next, area, size, type, size);
    printf(YELLOW "new area n %d of type %d and size %lu, unset size : %lu" END "\n", i, type, area->next->size, area->unset_size);
    return(get_block(area, size));
}

t_block     *get_block(t_area *area, size_t size) {
    
    t_block *block;

    block = check_free_block(area, size);
    printf("got block of size : %lu and size of block : %lu, occupied size of area before new block : %lu\n", block->size, sizeof(block), area->occupied);
    area->occupied += sizeof(block) + block->size;
    printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
    if (area->type == LARGE)
        area->full = 1;
    return(block);
}

void        init_area(t_area *area, t_area *prev, size_t size, int type, size_t original_size) {
    area->first_block = (t_block *)AREA_MEM(area);
    area->size = get_page_size(type, size);
    area->type = type;
    area->unset_size = area->size;
    area->occupied = 0;
    area->full = 0;
    area->prev = prev;
    area->next = NULL;
    
    area->first_block->size = original_size;
    area->unset_size -= sizeof(area->first_block) + area->first_block->size;
}

t_area      *request_memory(t_area *prev, size_t size) {
    
    t_area *new_alloc;

    if ((new_alloc = mmap(prev, size, PROT_READ|PROT_WRITE|PROT_EXEC,\
        MAP_ANON|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return(NULL);
    return(new_alloc);
}