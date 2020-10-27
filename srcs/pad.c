/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:47:40 by user42            #+#    #+#             */
/*   Updated: 2020/10/15 12:00:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*block_mem(t_block *block)
{
	return (void *)(block) + align_size(sizeof(t_block), 16);
}

void		*area_mem(t_area *area)
{
	return (void *)(area) + align_size(sizeof(t_area), 16);
}

void		*block_next(t_block *block)
{
	return (void*)(block_mem(block) + block->size);
}

void		*area_next(t_area *area)
{
	return (void*)(area_mem(area) + area->size);
}
