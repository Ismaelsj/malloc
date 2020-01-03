/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:49:15 by IsMac             #+#    #+#             */
/*   Updated: 2020/01/03 13:34:17 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap      new_heap(int type, size_t size)
{
    t_area  *new_area;
    t_heap  new_heap;

    new_area = request_memory(0, get_page_size(type, size));
    init_area(new_area, NULL, size, type);
    new_heap.type = type;
    new_heap.first_area = new_area;
    lock_area(new_area);
    return(new_heap);
}
