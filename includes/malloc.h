/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:07:19 by isidibe-          #+#    #+#             */
/*   Updated: 2019/12/31 11:27:10 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
# define MALLOC_H
// # include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# include <stdlib.h>

# define NB_BLOCKS		100

# define TINY_BLOCK		1024
# define SMALL_BLOCK	4096

# define BLOCK_MEM(block)       (void *)(block + 1)
# define AREA_MEM(area)         (void *)(area + 1)
# define BLOCK_NEXT(block)      BLOCK_MEM(block) + block->size
# define AREA_NEXT(area)        AREA_MEM(area) + area->size

// colors
#define RED     "\x1b[31m"  // free
#define GREEN   "\x1b[32m"  // malloc
#define YELLOW  "\x1b[33m"  // realloc
#define BLUE    "\x1b[34m"  // area
#define MAGENTA "\x1b[35m"  // block
#define CYAN    "\x1b[36m"  // merge block
#define GREY    "\x1b[90m"  // search block
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
    unsigned int        crc32;
	size_t				size;
    int                 busy;
	struct s_block		*prev;
	struct s_block		*next;
}						t_block;

typedef struct          s_area
{
    unsigned int        crc32;
    t_block             *first_block;
    int                 type;
    size_t				size;
    size_t              unset_size;
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

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

// areas
t_block     *check_free_area(int type, size_t size);
// void        init_area(t_area *area, t_area *prev, size_t size, int type, size_t original_size);
void        init_area(t_area *area, t_area *prev, size_t size, int type);
t_block     *append_new_area(t_area *area, size_t size);
t_block     *get_block(t_area *area, size_t size);

// blocks
t_block     *check_free_block(t_area *area, size_t size);
t_block     *append_new_block(t_block *prev, size_t size);
void        init_new_block(t_block *new_block, size_t size);
void        init_block(t_block *block, size_t size);

// merge block
int          check_mergeable_block(t_area *area, t_block *block, size_t size);
void        create_intermediate_block(t_block *block, size_t wanted_size);

// free
void    check_free_alloc(t_block *block, size_t size);
void    free_area(t_area *area);
void    free_block(t_area *area, t_block *block);

// show allocation
void    show_alloc_mem(void);

// size
size_t  get_header_size(void);
size_t  align_size(size_t size, size_t mult);
size_t  get_page_size(int type, size_t size);

// search
t_area  *retrieve_area(void *ptr);
t_block *retrieve_block(t_area *area, void *ptr);

// memory request
t_area      *request_memory(t_area *prev, size_t size);

// init
t_heap      new_heap(int type, size_t large_size);

// utils
int  	        choose_pool(size_t size);
size_t			    get_pool_size(int type);
size_t	        ft_strlen(char *str);
void	        ft_bzero(void *s, size_t n);
void	        ft_bchr(void *s, int c, size_t n);
void	        *ft_memcpy(void *s1, const void *s2, size_t n);
void	        ft_putendl(char const *s);
void            ft_iprint(int n);
void	        ft_putstr(char *str);
void		    ft_umaxtoa_base(unsigned long long nb, int nb_base);
unsigned int 	crc32(int *key, size_t len);
unsigned int	get_area_crc32(t_area *area);
void	        lock_area(t_area *area);
unsigned int	get_block_crc32(t_block *block);
void	        lock_block(t_block *block);

#endif