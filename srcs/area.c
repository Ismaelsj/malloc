/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/12 14:50:32 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *check_free_area(int type, size_t size)
{
    t_area  *area;
    t_block *block;
    int     i;
    
    i = 0;
    if (g_type[type].first_area == NULL)
    {
        // ft_putendl(BLUE "   create new first area" END);
        g_type[type] = init_heap(type, size);
    }
    // ft_putstr(BLUE "    checking area of type ");
    // ft_iprint(type);
    // ft_putendl("");
    area = g_type[type].first_area;
    // ft_putendl("    loop over areas :");
    while (area)
    {
        if (get_area_crc32(area) != area->crc32)
        {
            // ft_putendl(BLUE "        area corrupted ! exit.");
            return(NULL);
        }
        // ft_putstr(BLUE "         area n ");
        // ft_iprint(i);
        // ft_putstr(" of size : ");
        // ft_iprint(area->size);
        // ft_putstr(", type : ");
        // ft_iprint(area->type);
        // ft_putstr(", occupied size : ");
        // ft_iprint(area->occupied);
        // ft_putendl("");
        if (area->occupied + (align_size(sizeof(t_block), 16) + size)
            <= area->size && !area->full)
        {
            // ft_putstr("         foud free area of size ");
            // ft_iprint(area->size);
            // ft_putendl(" try to find a block");
            block = get_block(area, size);
            if (block)
                return(block);
        }
        i++;
        if (!area->next)
            break;
        area = area->next;
    }
    // ft_putendl("    get new area" END);
    if ((area = append_new_area(area, size)) == NULL)
        return(NULL);
    // ft_putstr(BLUE "   init new area of size ");
    // ft_iprint(size);
    // ft_putendl("");
    // ft_putendl("    area ready, try to find a block :");
    return(get_block(area, size));
}

t_block     *get_block(t_area *area, size_t size)
{ 
    t_block *block;

    // ft_putendl("    try to find a block" END);
    if ((block = check_free_block(area, size)) == NULL)
    {
        if (!area->next && area->unset_size
            < align_size(sizeof(t_block), 16) + size)
        {
            // ft_putendl("new area needed");
            if ((area = append_new_area(area, size)) == NULL)
                return(NULL);
            return(get_block(area, size));
        }
        // ft_putendl("no able to find/create block returning NULL");
        return(NULL);
    }
    // ft_putendl(BLUE "   got new block");
    area->occupied += align_size(sizeof(t_block), 16) + block->size;
    if (area->type == LARGE)
    {
        // ft_putendl("    LARGE area, full");
        area->full = 1;
    }
    lock_area(area);
    // ft_putendl("    return block" END);
    return(block);
}

t_area         *append_new_area(t_area *prev, size_t size)
{
    t_area *new_area;

    // ft_putendl("append new area ");
    if ((new_area = request_memory(AREA_NEXT(prev),\
        get_page_size(prev->type, size))) == NULL)
        return(NULL);
    init_area(new_area, prev, size, prev->type);
    prev->next = new_area;
    lock_area(prev);
    return(new_area);
}

t_area      *request_memory(t_area *prev, size_t size)
{
    t_area *new_alloc;

    if ((new_alloc = mmap(prev, size, PROT_READ|PROT_WRITE|PROT_EXEC,\
        MAP_ANONYMOUS|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return(NULL);
    return(new_alloc);
}