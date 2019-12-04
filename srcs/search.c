/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:34:50 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/04 10:42:57 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *retrieve_block(t_area *area, void *ptr) {

    t_block *block;

    if (area == NULL)
        return(NULL);
    block = area->first_block;
    while (block) {
        if (BLOCK_MEM(block) == ptr)
            return(block);
        block = block->next;
    }
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
    while (type <= LARGE) {
        printf("searching in area of type %d\n", type);
        area = g_type[type].first_area;
        i = 0;
        while (area) {
            printf("searching in area n %d\n", i);
            block = area->first_block;
            j = 0;
            while (block) {
                printf("searching for block n %d\n", j);
                if (BLOCK_MEM(block) == ptr) {
                    printf("blockn n %d, found in area n %d, of type %d\n", j, i, type);
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
    return(NULL);
}