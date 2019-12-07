/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/07 15:38:32 by isidibe-         ###   ########.fr       */
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
    size_t      tmp_size;
    unsigned long long tmp;
    int i;

    i = 0;
    most_fited_block = NULL;
    block = area->first_block;
    // printf("loop over blocks :\n");
    ft_putendl(MAGENTA "        loop over blocks");
    while (block) {
        // printf("    block n %d of size %lu, busy %d\n", i, block->size, block->busy);
        ft_putstr("            block n ");
        ft_iprint(i);
        ft_putstr(" of size ");
        ft_iprint(block->size);
        ft_putstr(" at addr : ");
        ft_umaxtoa_base((unsigned long long)block, 16);
        ft_putstr("         CRC32 : ");
        ft_umaxtoa_base((unsigned long long)crc32((void*)block, 8), 10);
        // ft_putendl("");
        if (block->busy == 0) {
            ft_putstr("            block not busy of size : ");
            ft_iprint(block->size);
            ft_putendl("");
            if (block->size < size) {
                // printf("found unused block of size %lu, try to merge/extend it:\n", block->size);
                ft_putendl("            found block to small, try to merge/extend blocks :" END);
                if (check_mergeable_block(area, block, size) == 1) {
                    ft_putendl(MAGENTA "            block merged/extended, returning it" END);
                    return(block);
                }
                else {
                    ft_putendl(MAGENTA "            block not mergeable or extendable");
                    // sleep(1);
                }
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
            ft_putendl("            no next block, exit loop:");
            break;
        }
        tmp = (unsigned long long)block;
        tmp_size = block->size;
        block = block->next;
        ft_putstr("             diff block, block->next addr : ");
        ft_umaxtoa_base((unsigned long long)block - tmp, 10);
        ft_putstr("                                     -> ");
        ft_umaxtoa_base(((unsigned long long)block - tmp) - tmp_size, 10);
        if (((unsigned long long)block - tmp) == 0)
            sleep(1);
    }
    if (most_fited_block != NULL) {
        ft_putendl("        init found block");
        create_intermediate_block(most_fited_block, size);
        init_block(most_fited_block, size);
        ft_putendl(MAGENTA "        returning block" END);
        // sleep(1);
        return(most_fited_block);
    }
    ft_putendl("        no block found, append new one");
    block->next = append_new_block(block, size);
    ft_putendl("new block created");
    area->unset_size -= sizeof(t_block) + block->size;
    // printf(BLUE "append new block n %d, of size %lu, area unset size : %lu" END "\n", i, block->next->size, area->unset_size);
    ft_putendl("        block created, returning it" END);
    // sleep(1);
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size) {

    t_block *new_block;

    // printf("append new block\n");
    ft_putendl("append new block 1");
    new_block = BLOCK_NEXT(prev);
    ft_putendl("append new block 2");
    new_block->size = size;
    // ft_putendl("append new block 3");
    new_block->prev = prev;
    // ft_putendl("append new block 4");
    new_block->next = NULL;
    // ft_putendl("append new block 5");
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