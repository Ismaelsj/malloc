/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:28:15 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/08 16:20:44 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t  get_header_size(void) {
    return(align_size(sizeof(t_block), 16));
}

size_t  align_size(size_t size, size_t mult) {
    if (size == 0)
        return(mult);
    return(((((size) - 1) / mult) * mult) + mult);
}

size_t  get_page_size(int type, size_t size) {
    
    size_t  page;
    
    if (type == TINY)
        page = align_size((TINY_BLOCK + get_header_size()) * NB_BLOCKS, getpagesize());
    else if (type == SMALL)
        page = align_size((SMALL_BLOCK + get_header_size()) * NB_BLOCKS, getpagesize());
    else
        page = align_size((size + get_header_size()) * NB_BLOCKS, getpagesize());
    return(page);
}