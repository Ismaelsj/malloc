/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:03:46 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 16:33:11 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
	t_block *block;
	int		type;
	size_t	aligned_size;

	if (nmemb == 0 || size == 0)
		return (NULL);
	aligned_size = align_size(nmemb * size, 16);
	type = choose_pool(aligned_size);
	pthread_mutex_lock(&g_mutex);
	if ((block = check_free_area(type, aligned_size)) == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	ft_bzero(block_mem(block), aligned_size);
	pthread_mutex_unlock(&g_mutex);
	return (block_mem(block));
}
