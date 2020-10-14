/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:02:11 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 17:16:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap			g_type[3] = {{.type=TINY, .first_area=NULL}, {.type=SMALL,\
		.first_area=NULL}, {.type=LARGE, .first_area=NULL}};

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	int		type;
	t_block	*block;

	size = align_size(size, 16);
	type = choose_pool(size);
	pthread_mutex_lock(&g_mutex);
	if ((block = check_free_area(type, size)) == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	return (BLOCK_MEM(block));
}
