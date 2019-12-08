/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:02:11 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/07 19:55:47 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

t_heap           g_type[3] = {{.type=TINY, .first_area=NULL}, {.type=SMALL, .first_area=NULL}, {.type=LARGE, .first_area=NULL}};

int  	choose_pool(size_t size)
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

	ft_putendl(GREEN "==== MALLOC ====");
	// printf("sizeof t_area : %lu\nsizeof t_block : %lu\n", sizeof(t_area), sizeof(t_block));
    // printf("asked size size before alignement : %lu\n", size);
	size = align_size(size, 16);
	ft_putstr(GREEN "got size of : ");
	ft_iprint(size);
	ft_putendl("");
	// printf("asked size after alignement : %lu\n", size);
    type = choose_pool(size);
	ft_putstr("got pool of type : ");
	ft_iprint(type);
	ft_putendl("\nsize aligned, pool chosen, trying to get a block :" END);
	if ((block = check_free_area(type, size)) == NULL)
		return(NULL);
	ft_putendl("got block ready to return");
	return(BLOCK_MEM(block));
}