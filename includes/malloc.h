/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:07:19 by isidibe-          #+#    #+#             */
/*   Updated: 2019/11/11 17:05:42 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# define NB_BLOCKS		100
# define TINY_BLOCK		512
# define SMALL_BLOCK	1024

# define ALIGN_MULTIPLE 16

enum					e_size
{
	TINY,
	SMALL,
	LARGE
};

typedef struct			s_block
{
	size_t				size;
    int                 busy;
    void                *mem;
	struct s_block		*prev;
	struct s_block		*next;
}						t_block;

typedef struct          s_area
{
    t_block             *first_block;
    size_t				size;
    int                 full;    
    struct s_area		*prev;
	struct s_area		*next;
}                       t_area;

typedef struct          s_heap
{
    int                 type;
    t_area              *first_area;
}                       t_heap;

extern t_heap           g_type[3];

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

// areas
t_block     *check_free_area(int type, size_t size);
void        init_area(t_area *area, t_area *prev, size_t size);

// blocks
t_block     *check_free_block(t_block *first_block, size_t size);
t_block     *init_new_block(t_block *prev, size_t size);

// size
size_t  get_header_size(void);
size_t  align_size(size_t size, size_t mult);
size_t  get_page_size(int type, size_t size);

// memory request
t_area      *request_memory(t_area *prev, size_t size);

// init
t_heap      new_heap(int type, size_t large_size);

// utils
void	ft_bzero(void *s, size_t n);

#endif