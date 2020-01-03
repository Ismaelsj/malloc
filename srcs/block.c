/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:42 by isidibe-          #+#    #+#             */
/*   Updated: 2020/01/03 12:55:24 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


void        init_block(t_block *block, size_t size)
{
    block->size = size;
    block->busy = 1;
    lock_block(block);
}

t_block             *check_free_block(t_area *area, size_t size)
{
    t_block     *block;
    t_block     *most_fited_block;
    size_t      tmp_size;
    unsigned long long tmp;
    int i;

    i = 0;
    most_fited_block = NULL;
    block = area->first_block;
    ft_putendl(MAGENTA "        loop over blocks");
    while (block)
    {
        if (get_block_crc32(block) != block->crc32)
        {
            ft_putstr("block n ");
            ft_iprint(i);
            ft_putendl(" corrupted." END);
            return(NULL);
        }
        if (block->busy == 0)
        {
            ft_putstr("            block n ");
            ft_iprint(i);
            ft_putstr(" not busy of size ");
            ft_iprint(block->size);
            ft_putendl("");
            if (block->size >= size)
            {
                if (most_fited_block == NULL || block->size < most_fited_block->size)
                {
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
        if (!block->next)
        {
            ft_putendl("            no next block, exit loop:");
            break;
        }
        tmp = (unsigned long long)block;
        tmp_size = block->size;
        block = block->next;
        if (((unsigned long long)block - tmp) == 0)
            sleep(1);
    }
    if (most_fited_block != NULL)
    {
        ft_putendl("        init found block");
        most_fited_block->busy = 1;
        create_intermediate_block(most_fited_block, size, area->type, 1);
        init_block(most_fited_block, size);
        ft_putendl(MAGENTA "        returning block" END);
        return(most_fited_block);
    }

    ft_putendl("        no block found, append new one");
    if (area->unset_size < align_size(sizeof(t_block), 16) + size)
    {
        ft_putendl("No enough space to append a new block");
        return(NULL);
    }
    block->next = append_new_block(block, size);
    lock_block(block);
    ft_putendl("new block created");
    area->unset_size -= align_size(sizeof(t_block), 16) + block->next->size;
    ft_putendl("        block created, returning it" END);
    return(block->next);
}

t_block         *append_new_block(t_block *prev, size_t size)
{
    t_block *new_block;

    ft_putendl("append new block ");
    new_block = BLOCK_NEXT(prev);
    new_block->size = size;
    new_block->prev = prev;
    new_block->next = NULL;
    new_block->busy = 1;
    lock_block(new_block);
    return(new_block);
}

void            init_new_block(t_block *new_block, size_t size)
{
    new_block->size = size;
    new_block->busy = 0;
    new_block->prev = NULL;
    new_block->next = NULL;
}