/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:49:15 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/07 19:42:09 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap      new_heap(int type, size_t original_size) {
    t_area  *new_area;
    t_heap  new_heap;
    size_t size;

    if (type == TINY)
        size = TINY_BLOCK;
    else if (type == SMALL)
        size = SMALL_BLOCK;
    else
        size = original_size;

    new_area = request_memory(0, get_page_size(type, size));
    // printf("got new memory for area of size : %lu at address :%p, rlimit : %p\n", get_page_size(type, size), &new_area, &new_area + get_page_size(type, size));
    // printf("        size : %lu\n", size);
    init_area(new_area, NULL, size, type, original_size);
    // printf(YELLOW "first area of type %d and size %lu, unset size : %lu" END "\n", type, new_area->size, new_area->unset_size);
    // printf("new %d area of size %lu -> %lu at adress : %p\n", TINY, size, get_page_size(type, size), &new_area);
    new_heap.type = type;
    new_heap.first_area = new_area;
    lock_area(new_area);
    return(new_heap);
}
