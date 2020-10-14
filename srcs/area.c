/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:56 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/12 16:31:14 by IsMac            ###   ########.fr       */
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
        g_type[type] = init_heap(type, size);
    }
    area = g_type[type].first_area;
    while (area)
    {
        if (get_area_crc32(area) != area->crc32)
            return(NULL);
        if (area->occupied + (align_size(sizeof(t_block), 16) + size)
            <= area->size && !area->full)
        {
            block = get_block(area, size);
            if (block)
                return(block);
        }
        i++;
        if (!area->next)
            break;
        area = area->next;
    }
    if ((area = append_new_area(area, size)) == NULL)
        return(NULL);
    return(get_block(area, size));
}

t_block     *get_block(t_area *area, size_t size)
{
    t_block *block;

    if ((block = check_free_block(area, size)) == NULL)
    {
        if (!area->next && area->unset_size
            < align_size(sizeof(t_block), 16) + size)
        {
            if ((area = append_new_area(area, size)) == NULL)
                return(NULL);
            return(get_block(area, size));
        }
        return(NULL);
    }
    area->occupied += align_size(sizeof(t_block), 16) + block->size;
    if (area->type == LARGE)
    {
        area->full = 1;
    }
    lock_area(area);
    return(block);
}

t_area         *append_new_area(t_area *prev, size_t size)
{
    t_area *new_area;

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