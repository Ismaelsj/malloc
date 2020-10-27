/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:34:50 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 19:07:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block			*retrieve_block(t_area *area, void *ptr)
{
	t_block	*block;

	if (area == NULL)
		return (NULL);
	block = area->first_block;
	while (block)
	{
		if (get_block_crc32(block) != block->crc32)
			return (NULL);
		if (block_mem(block) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_area			*retrieve_area(void *ptr)
{
	t_area	*area;
	t_block	*block;
	int		type;

	type = 0;
	while (type <= LARGE)
	{
		area = g_type[type].first_area;
		while (area)
		{
			block = area->first_block;
			while (block)
			{
				if (get_block_crc32(block) != block->crc32)
					return (NULL);
				if (block_mem(block) == ptr)
					return (area);
				block = block->next;
			}
			area = area->next;
		}
		type++;
	}
	return (NULL);
}
