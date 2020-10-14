/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:02:22 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 16:22:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned int	crc32(int *key, size_t len)
{
	int				j;
	unsigned int	i;
	unsigned int	byte;
	unsigned int	crc;
	unsigned int	mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (i < len)
	{
		byte = (unsigned int)key[i];
		crc = crc ^ byte;
		j = 7;
		while (j >= 0)
		{
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
			j--;
		}
		i++;
	}
	return (~crc);
}

void			lock_block(t_block *block)
{
	size_t	len;

	if (!block)
		return ;
	len = sizeof(block) - sizeof(unsigned int);
	block->crc32 = crc32((void*)block + sizeof(unsigned int), len);
}

unsigned int	get_block_crc32(t_block *block)
{
	size_t	len;

	if (!block)
		return (0);
	len = sizeof(block) - sizeof(unsigned int);
	return (crc32((void*)block + sizeof(unsigned int), len));
}

void			lock_area(t_area *area)
{
	size_t len;

	if (!area)
		return ;
	len = sizeof(area) - sizeof(unsigned int);
	area->crc32 = crc32((void*)area + sizeof(unsigned int), len);
}

unsigned int	get_area_crc32(t_area *area)
{
	size_t len;

	if (!area)
		return (0);
	len = sizeof(area) - sizeof(unsigned int);
	return (crc32((void*)area + sizeof(unsigned int), len));
}
