/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/05 17:33:32 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


void        init_block(t_block *block, size_t size) {
    block->size = size;
    block->busy = 1;
}

t_block             *check_free_block(t_area *area, size_t size) {
    
    t_block     *block;
    t_block     *most_fited_block;
    int i;

    i = 0;
    most_fited_block = NULL;
    block = area->first_block;
    // printf("loop over blocks :\n");
    ft_putendl(MAGENTA "        loop over blocks");
    while (block) {
        // printf("    block n %d of size %lu, busy %d\n", i, block->size, block->busy);
        ft_putendl("            block");
        if (block->busy == 0) {
            ft_putendl("            block not busy");
            if (block->size < size) {
                // printf("found unused block of size %lu, try to merge/extend it:\n", block->size);
                ft_putendl("            found block to small, try to merge/extend blocks :" END);
                if (check_mergeable_block(area, block, size) == 1) {
                    ft_putendl(MAGENTA "            block merged/extended, returning it" END);
                    return(block);
                }
                else
                    ft_putendl(MAGENTA "            block not mergeable or extendable");
            }
            else if (block->size >= size) {
                // printf("found unused block of size %lu\n", block->size);
                if (most_fited_block == NULL || block->size < most_fited_block->size) {
                    ft_putstr("            found big enough block of size ");
                    ft_iprint(block->size);
                    ft_putstr(" for asked size ");
                    ft_iprint(size);
                    ft_putendl(", saving it");
                    most_fited_block = block;
                }
            }
        }
        i++;
        if (!block->next) {
            // ft_putendl("            no next block");
            break;
        }
        block = block->next;
    }
    if (most_fited_block != NULL) {
        ft_putendl("        init found block");
        init_block(most_fited_block, size);
        ft_putendl("        returning block" END);
        return(most_fited_block);
    }
    ft_putendl("        no block found, append new one");
    block->next = append_new_block(block, size);
    area->unset_size -= sizeof(block) + block->size; 
    // printf(BLUE "append new block n %d, of size %lu, area unset size : %lu" END "\n", i, block->next->size, area->unset_size);
    ft_putendl("        block created, returning it" END);
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size) {

    t_block *new_block;

    // printf("append new block\n");
    new_block = BLOCK_NEXT(prev);
    new_block->size = size;
    new_block->prev = prev;
    new_block->next = NULL;
    new_block->busy = 1;

    return(new_block);
}

void            init_new_block(t_block *new_block, size_t size) {

    new_block->size = size;
    new_block->busy = 0;
    new_block->prev = NULL;
    new_block->next = NULL;
    // printf(BLUE "new block of size %lu" END "\n", new_block->size);
}