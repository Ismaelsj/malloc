/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:34:50 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/30 15:08:30 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *retrieve_block(t_area *area, void *ptr) {

    t_block *block;
    int i;

    ft_putendl(GREY "searching block :");
    if (area == NULL) {
        ft_putendl(GREY "area NULL" END);
        return(NULL);
    }
    i = 0;
    block = area->first_block;
    while (block) {
        if (BLOCK_MEM(block) == ptr) {
            ft_putstr(GREY "coresponding block of size ");
            ft_iprint(block->size);
            ft_putendl(" found" END);
            return(block);
        }
        i++;
        block = block->next;
    }
    ft_putendl(GREY "block not found" END);
    return(NULL);
}


t_area  *retrieve_area(void *ptr) {

    t_area  *area;
    t_block *block;
    int     type;
    int     i;
    int     j;

    type = 0;
    i = 0;
    j = 0;
    ft_putendl(GREY "searching area :");
    while (type <= LARGE) {
        ft_putstr("searching in area of type ");
        ft_iprint(type);
        ft_putendl("");
        // printf("searching in area of type %d\n", type);
        area = g_type[type].first_area;
        i = 0;
        while (area) {
            ft_putstr("searching in area n ");
            ft_iprint(i);
            ft_putendl("");
            // printf("searching in area n %d\n", i);
            block = area->first_block;
            j = 0;
            while (block) {
                if (BLOCK_MEM(block) == ptr) {
                    ft_putstr("coresponding block n ");
                    ft_iprint(j);
                    ft_putstr(", found in area n ");
                    ft_iprint(i);
                    ft_putstr(", of type ");
                    ft_iprint(type);
                    ft_putendl("" END);
                    // printf("block n %d, found in area n %d, of type %d\n", j, i, type);
                    return(area);
                }
                block = block->next;
                j++;
            }
            area = area->next;
            i++;
        }
        type++;
    }
    ft_putendl("area not found" END);
    return(NULL);
}