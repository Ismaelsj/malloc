/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:28:15 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 16:27:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		get_header_size(void)
{
	return (align_size(sizeof(t_block), 16));
}

size_t		align_size(size_t size, size_t mult)
{
	if (size == 0)
		return (mult);
	return (((((size) - 1) / mult) * mult) + mult);
}

size_t		get_page_size(int type, size_t size)
{
	size_t	page;

	if (type == TINY)
		page = align_size((TINY_BLOCK + get_header_size()) * NB_BLOCKS,\
				getpagesize()) + align_size(sizeof(t_area), 16);
	else if (type == SMALL)
		page = align_size((SMALL_BLOCK + get_header_size()) * NB_BLOCKS,\
				getpagesize()) + align_size(sizeof(t_area), 16);
	else
		page = align_size((size + get_header_size()),\
				getpagesize()) + align_size(sizeof(t_area), 16);
	return (page);
}
