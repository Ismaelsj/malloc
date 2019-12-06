/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/06 15:07:20 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *check_free_area(int type, size_t size) {
    
    t_area  *area;
    int     i;
    
    i = 0;
    if (g_type[type].first_area == NULL) {
        // printf(GREEN "create first area of type %d" END "\n", type);
        ft_putendl(BLUE "   create new first area" END);
        g_type[type] = new_heap(type, size);
    }
    ft_putstr(BLUE "    checking area of type ");
    ft_iprint(type);
    ft_putendl("");
    area = g_type[type].first_area;
    // printf("loop over areas :\n");
    ft_putendl("    loop over areas :");
    while (area) {
        // printf("    area n %d: occupied/size : %lu/%lu, full %d, unset size : %lu\n", i, area->occupied, area->size, area->full, area->unset_size);
        ft_putstr("         area of size : ");
        ft_iprint(area->size);
        ft_putstr(", type : ");
        ft_iprint(area->type);
        ft_putstr(", occupied size : ");
        ft_iprint(area->occupied);
        ft_putendl("");
        if (area->occupied + (sizeof(t_block) + size) <= area->size && !area->full) {
            ft_putstr("         foud free area of size ");
            ft_iprint(area->size);
            ft_putendl(" try to find a block");
            return(get_block(area, size));
        }
        i++;
        if (!area->next)
            break;
        area = area->next;
    }
    ft_putendl("    get new area" END);
    if ((area->next = request_memory(AREA_NEXT(area), get_page_size(type, size))) == NULL)
        return(NULL);
    ft_putstr(BLUE "   init new area of size ");
    ft_iprint(size);
    ft_putendl("");
    init_area(area->next, area, size, type, size);
    ft_putendl("    area ready, try to find a block :");
    area = area->next;
    // printf(YELLOW "new area n %d of type %d and size %lu, unset size : %lu" END "\n", i, type, area->next->size, area->unset_size);
    return(get_block(area, size));
}

t_block     *get_block(t_area *area, size_t size) {
    
    t_block *block;

    ft_putendl("    try to find a block" END);
    block = check_free_block(area, size);
    ft_putendl(BLUE "   got new block");
    // printf("got block of size : %lu and size of block : %lu, occupied size of area before new block : %lu\n", block->size, sizeof(block), area->occupied);
    area->occupied += sizeof(block) + block->size;
    // printf("occupied size of area : %lu/%lu\n", area->occupied, area->size);
    if (area->type == LARGE) {
        ft_putendl("    LARGE area, full");
        area->full = 1;
    }
    ft_putendl("    return block" END);
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
        MAP_ANONYMOUS|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return(NULL);
    return(new_alloc);
}