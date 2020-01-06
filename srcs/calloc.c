/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:03:46 by isidibe-          #+#    #+#             */
/*   Updated: 2020/01/06 11:34:59 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *calloc(size_t nmemb, size_t size) {
    
    t_block *block;
    int     type;
    size_t  aligned_size;

    // ft_putendl(UNKNOWN "==== CALLOC ====");
    if (nmemb == 0 || size == 0) {
        // ft_putendl(UNKNOWN"zero !");
        return(NULL);
    }

    // ft_putstr(UNKNOWN "");
    // ft_iprint(nmemb);
    // ft_putstr(" blocks of size ");
    // ft_iprint(size);
    // ft_putendl("");
    aligned_size = align_size(nmemb*size, 16);
    type = choose_pool(aligned_size);
    pthread_mutex_lock(&g_mutex);
    if ((block = check_free_area(type, aligned_size)) == NULL)
	{
		// ft_putendl(UNKNOWN"calloc : failed");
		pthread_mutex_unlock(&g_mutex);
		return(NULL);
	}
    pthread_mutex_unlock(&g_mutex);
    // ft_bzero(BLOCK_MEM(block), aligned_size);
    // ft_putendl(UNKNOWN "got block ready to return" END);
	return(BLOCK_MEM(block));
}