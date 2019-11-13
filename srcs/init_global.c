/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:49:15 by IsMac             #+#    #+#             */
/*   Updated: 2019/11/11 18:57:02 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap      new_heap(int type, size_t large_size) {
    t_area  *new_area;
    t_heap  new_heap;
    size_t size;

    if (type == TINY)
        size = TINY_BLOCK;
    else if (type == SMALL)
        size = SMALL_BLOCK;
    else
        size = large_size;

    new_area = request_memory(0, get_page_size(type, size));
    init_area(new_area, NULL, size);
    printf("new %d area of size %lu -> %lu at adress : %p\n", TINY, size, get_page_size(type, size), new_area);
    new_heap.type = type;
    new_heap.first_area = new_area;
    return(new_heap);
}