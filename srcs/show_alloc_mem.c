/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:09:31 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/30 16:38:11 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            show_area_info(t_area *area) {

    if (area->type == TINY)
        ft_putstr("TINY :");
    else if (area->type == SMALL)
        ft_putstr("SMALL :");
    else
        ft_putstr("LARGE :");
    ft_umaxtoa_base((unsigned long long)AREA_MEM(area), 16);
}

void            show_block_info(t_block *block) {

    ft_putstr("    ");
    ft_umaxtoa_base((unsigned long long)BLOCK_MEM(block), 16);
    ft_putstr(" - ");
    ft_umaxtoa_base((unsigned long long)(BLOCK_NEXT(block) - 1), 16);
    ft_putstr(" : ");
    ft_umaxtoa_base((unsigned long long)block->size, 10);
    ft_putendl(" octets");
}

void            show_total(size_t total) {
    
    ft_putstr("Total : ");
    ft_umaxtoa_base((unsigned long long)total, 10);
    ft_putendl(" octets");
}

void			show_alloc_mem(void) {

    t_area  *area;
    t_block *block;
    size_t  total;
    int     type;

    type = 0;
    total = 0;
    while (type < 3) {
        area = g_type[type].first_area;
        while (area) {
            show_area_info(area);
            block = area->first_block;
            while (block) {
                show_block_info(block);
                total += block->size;
                block = block->next;
            }
            area = area->next;
            ft_putendl("");
        }
        type++;
    }
    show_total(total);
}