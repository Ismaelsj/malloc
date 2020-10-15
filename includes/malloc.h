/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:07:19 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/15 12:46:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# define NB_BLOCKS			100
# define TINY_BLOCK			1024
# define SMALL_BLOCK		1024000
# define ALIGN_MULTIPLE 	16

enum						e_size
{
	TINY,
	SMALL,
	LARGE
};

typedef struct				s_block
{
	unsigned int			crc32;
	size_t					size;
	int						busy;
	struct s_block			*prev;
	struct s_block			*next;
}							t_block;

typedef struct				s_area
{
	unsigned int			crc32;
	t_block					*first_block;
	int						type;
	size_t					size;
	size_t					unset_size;
	size_t					occupied;
	int						full;
	struct s_area			*prev;
	struct s_area			*next;
}							t_area;

typedef struct				s_heap
{
	int						type;
	t_area					*first_area;
}							t_heap;

extern pthread_mutex_t		g_mutex;

extern t_heap				g_type[3];

void						free(void *ptr);
void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						*calloc(size_t nmemb, size_t size);
void						show_alloc_mem();

void						*block_mem(t_block *block);
void						*area_mem(t_area *area);
void						*block_next(t_block *block);
void						*area_next(t_area *area);

t_block						*check_free_area(int type, size_t size);
void						init_area(t_area *area, t_area *prev, size_t size,\
									int type);
t_area						*append_new_area(t_area *prev, size_t size);
t_block						*get_block(t_area *area, size_t size);
t_block						*check_free_block(t_area *area, size_t size);
t_block						*append_new_block(t_block *prev, size_t size);
void						init_block(t_block *block, size_t size);

int							check_mergeable_block(t_area *area, t_block *block,\
									size_t size);
void						create_intermediate_block(t_block *block,\
									size_t wanted_size, int type, int defrag);
void						check_free_alloc(t_block *block, size_t size);
void						free_area(t_area *area);
void						free_block(t_area *area, t_block *block);
t_block						*defragment_block(t_block *block, int type);

void						show_alloc_mem(void);

size_t						get_header_size(void);
size_t						align_size(size_t size, size_t mult);
size_t						get_page_size(int type, size_t size);

t_area						*retrieve_area(void *ptr);
t_block						*retrieve_block(t_area *area, void *ptr);

t_area						*request_memory(t_area *prev, size_t size);

t_heap						init_heap(int type, size_t large_size);

int							choose_pool(size_t size);
size_t						get_pool_size(int type);
size_t						ft_strlen(char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_memcpy(void *s1, const void *s2, size_t n);
void						ft_putendl(char const *s);
void						ft_iprint(int n);
void						ft_putstr(char *str);
void						ft_umaxtoa_base(unsigned long long nb, int nb_base);
unsigned int				crc32(unsigned int *key, size_t len);
unsigned int				get_area_crc32(t_area *area);
void						lock_area(t_area *area);
unsigned int				get_block_crc32(t_block *block);
void						lock_block(t_block *block);

#endif
