/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:02:11 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/12 15:20:51 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdio.h>
// #include <string.h>

t_heap           	g_type[3] = {{.type=TINY, .first_area=NULL}, {.type=SMALL,\
						.first_area=NULL}, {.type=LARGE, .first_area=NULL}};

pthread_mutex_t 	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void        *malloc(size_t size)
{
    int 	type;
	t_block	*block;

	// ft_putendl(GREEN "==== MALLOC ====" END);
	// return(NULL);
	// ft_iprint(size);
	size = align_size(size, 16);
	// ft_putstr(GREEN "got size of : ");
	// ft_iprint(size);
	// ft_putendl("");
    type = choose_pool(size);
	// ft_putstr("got pool of type : ");
	// ft_iprint(type);
	// ft_putendl("\nsize aligned, pool chosen, trying to get a block :" END);
	pthread_mutex_lock(&g_mutex);
	if ((block = check_free_area(type, size)) == NULL)
	{
		// ft_putendl("malloc : failed");
		pthread_mutex_unlock(&g_mutex);
		return(NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	// ft_putendl(GREEN "got block ready to return" END);
	// show_alloc_mem();
	return(BLOCK_MEM(block));
}