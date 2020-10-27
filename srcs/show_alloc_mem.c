/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:09:31 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 11:58:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		show_area_info(t_area *area)
{
	if (area->type == TINY)
		ft_putstr("TINY :");
	else if (area->type == SMALL)
		ft_putstr("SMALL :");
	else
		ft_putstr("LARGE :");
	ft_umaxtoa_base((unsigned long long)area_mem(area), 16);
	ft_putendl("");
}

void		show_block_info(t_block *block)
{
	ft_putstr("    ");
	ft_umaxtoa_base((unsigned long long)block_mem(block), 16);
	ft_putstr(" - ");
	ft_umaxtoa_base((unsigned long long)(block_next(block) - 1), 16);
	ft_putstr(" : ");
	ft_umaxtoa_base((unsigned long long)block->size, 10);
	ft_putendl(" octets");
}

void		show_total(size_t total)
{
	ft_putstr("Total : ");
	ft_umaxtoa_base((unsigned long long)total, 10);
	ft_putendl(" octets");
}

void		show_alloc_mem(void)
{
	t_area	*area;
	t_block	*block;
	size_t	total;
	int		type;

	type = 0;
	total = 0;
	while (type < 3)
	{
		area = g_type[type].first_area;
		while (area)
		{
			show_area_info(area);
			block = area->first_block;
			while (block)
			{
				show_block_info(block);
				total += block->size;
				block = block->next;
			}
			area = area->next;
		}
		type++;
	}
	show_total(total);
}
