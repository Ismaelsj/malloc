/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:02:11 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/24 18:27:14 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

t_heap           g_type[3] = {{.type=TINY, .first_area=NULL}, {.type=SMALL, .first_area=NULL}, {.type=LARGE, .first_area=NULL}};

static int  ft_choose_pool(size_t size)
{
	if (size <= TINY_BLOCK)
		return (TINY);
	else if (size <= SMALL_BLOCK)
		return (SMALL);
	else
		return (LARGE);
}

void        *malloc(size_t size) {

    int 	type;
	t_block	*block;

	printf("sizeof t_area : %lu\nsizeof t_block : %lu\n", sizeof(t_area), sizeof(t_block));
    printf("size before alignement : %lu\n", size);
	size = align_size(size, 16);
	printf("size after alignement : %lu\n", size);
    type = ft_choose_pool(size);
	block = check_free_area(type, size);
	return(BLOCK_MEM(block));
}