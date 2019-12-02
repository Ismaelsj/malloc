/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:07:19 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/02 17:04:26 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
# define MALLOC_H
// # include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# define NB_BLOCKS		100
# define TINY_BLOCK		512
# define SMALL_BLOCK	1024

# define BLOCK_MEM(block)       (void *)(block + 1)
# define AREA_MEM(area)         (void *)(area + 1)
# define BLOCK_NEXT(block)      BLOCK_MEM(block) + block->size
# define AREA_NEXT(area)        AREA_MEM(area) + area->size

// colors
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"  // new heap
#define YELLOW  "\x1b[33m"  // new area
#define BLUE    "\x1b[34m"  // new block
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define END     "\x1b[0m"

// # define AREA_LIMIT(area, block, size) BLOCK_MEM(first_block) + area->size

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
	struct s_block		*prev;
	struct s_block		*next;
}						t_block;

typedef struct          s_area
{
    t_block             *first_block;
    int                 type;
    size_t				size;
    size_t              occupied;
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

void    ft_free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

// areas
t_block     *check_free_area(int type, size_t size);
void        init_area(t_area *area, t_area *prev, size_t size, int type, size_t original_size);
t_block     *append_new_area(t_area *area, size_t size);
t_block     *get_block(t_area *area, size_t size);

// blocks
t_block     *check_free_block(t_area *area, size_t size);
t_block     *append_new_block(t_block *prev, size_t size);
void        init_new_block(t_block *new_block, size_t size);
// t_block     *check_area_limit(t_area *area, t_block *block, size_t size);

// free
void    check_free_alloc(t_block *block, size_t size);
void    free_area(t_area *area);
// t_area  *get_area(t_block *first_block);
t_area  *get_area(void *ptr);

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
void	put_base(unsigned long long value, int base);

#endif