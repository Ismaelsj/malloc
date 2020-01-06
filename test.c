/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2020/01/06 10:24:49 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

char    *do_malloc(char *null, size_t size) {
    
    char    *str;

    (void*)null;
    // printf(GREEN "========= Mallocation =========\n");
    ft_putstr("size : ");
    ft_iprint(size);
    ft_putendl("");
    if ((str = (char *)malloc(sizeof(char) * size)) == NULL) {
        ft_putendl("NULL returned\n\n");
        return(NULL);
    }
    ft_bchr(str, 'm', size-1);
    ft_putendl(GREEN "malloc has succeeded\n\n" END);
    return(str);
}

char    *do_realloc(char *str, size_t size) {
    // printf(YELLOW "========= Reallocation =========\n");
    // if (str == NULL)
    //     return(NULL);
    // ft_putstr("from size : ");
    // ft_iprint(ft_strlen(str));
    ft_putstr("to size : ");
    ft_iprint(size);
    ft_putendl("");
    ft_putstr("size : ");
    ft_iprint(size);
    ft_putendl("");
    // ft_putstr(GREEN "ptr value : ");
    // ft_putstr(str);
    // ft_putendl("" END);
    if ((str = (char *)realloc(str, sizeof(char) * size)) == NULL) {
        ft_putendl("NULL returned\n\n");
        return(0);
    }
    ft_bchr(str, 'r', size-1);
    ft_putendl(GREEN "realloc has succeeded\n\n" END);
    return(str);
}

char    *do_free(char *str) {
    // printf(YELLOW "========= Free =========\n");
    free(str);
    ft_putendl(GREEN "pointer str freed\n\n" END);
    return(NULL);
}

typedef char* (*fptr)(char*, size_t);

typedef struct		s_test_ptr
{
    char            *str;
}	                t_test_ptr;

int main(void) {

    // t_block *block;

    // printf("%lu\n", align_size(sizeof(t_block), 16));
    // printf("%lu\n", sizeof(t_block), 16);
    // printf("%lu\n", align_size(sizeof(t_area), 16));
    // printf("%lu\n", sizeof(t_area), 16);
    // char *str;

    // str = (char *)malloc(sizeof(char) * 10);
    // return(0);
    // char *tmp = "Bonjour";
    // char *tmp2 = "yahyahyah aifu ruhseru hweur hewger reg reugweur giwoeubrguberwub goeurybgouyrb oeuyrbg";
    // char *str;
    // char *str2;

    // int i;
    // char *addr;

    // i = 0;
    // while(i < 1024) {
    //     addr = (char*)malloc(1024);
    //     addr[0] = 42;
    //     i++;
    // }
    // return(0);

    t_test_ptr  ptrs_test[200];
    fptr        ftab[3] = {&do_malloc, &do_realloc, &do_free};
    int         nb_action = 100;
    int         lower_ptr = 0, upper_ptr = 999;
    int         lower_act = 0, upper_act = 2;
    int         nb_iter = 199;
    int         max_alloc = 6024;
    int         min_alloc = 16;
    
    // init ptr to NULL
    for (int i=0; i < nb_iter; i++) {
        ptrs_test[i].str = NULL;
    }

    char *str;

    str = (char*)calloc(10, 10);
    return(0);

    // // random operations
    // for (int j = 0; j < nb_action; j++) {
    //     printf("-- operation n %d --\n", j);
    //     int ptr_index = (rand() % (upper_ptr - lower_ptr + 1)) + lower_ptr; 
    //     int act_index = (rand() % (upper_act - lower_act + 1)) + lower_act; 
    //     int size = (rand() % (99999 - 4 + 1)) + 4; 
    //     ptrs_test[ptr_index].str = ftab[act_index](ptrs_test[ptr_index].str, size);
    // }

    // malloc
    for (int k=0; k <= nb_iter; k++) {
        ft_putstr("    ==== malloc operation n ");
        ft_iprint(k);
        ft_putendl(" ====");
        size_t size = (rand() % (max_alloc - min_alloc + 1)) + min_alloc;
        ptrs_test[k].str = do_malloc(ptrs_test[k].str, size);
        if (ptrs_test[k].str == NULL)
            ft_putendl("********* MALLOC RETURNED NULL PTR *********");
    }


    // random free
    for (int k=0; k < (nb_iter - 50); k++) {
        // printf("    ==== random free operation n %d ====\n", k);
        ft_putstr("    ==== random free operation n ");
        ft_iprint(k);
        ft_putendl(" ====");
        size_t ptr = (rand() % (nb_iter - 0 + 1)) + 0;
        if (ptrs_test[ptr].str != NULL)
            ptrs_test[ptr].str = do_free(ptrs_test[ptr].str);
    }

    // random malloc
    for (int k=0; k <= nb_iter; k++) {
        ft_putstr("    ==== random malloc operation n ");
        ft_iprint(k);
        ft_putendl(" ====");
        size_t size = (rand() % (max_alloc - min_alloc + 1)) + min_alloc;
        size_t ptr = (rand() % (nb_iter - 0 + 1)) + 0;
        if (ptrs_test[ptr].str == NULL) {
            ptrs_test[ptr].str = do_malloc(ptrs_test[ptr].str, size);
            if (ptrs_test[ptr].str == NULL)
                ft_putendl("********* MALLOC RETURNED NULL PTR *********");
        }
    }

    // random realloc
    for (int k=0; k < (nb_iter - 50); k++) {
        // printf("    ==== realloc operation n %d ====\n", k);
        ft_putstr("    ==== random realloc operation n ");
        ft_iprint(k);
        ft_putendl(" ====");
        size_t size = (rand() % (max_alloc - min_alloc + 1)) + min_alloc;
        size_t ptr = (rand() % (nb_iter - 0 + 1)) + 0;
        ptrs_test[ptr].str = do_realloc(ptrs_test[ptr].str, size);
        if (ptrs_test[ptr].str == NULL)
            ft_putendl("********* REALLOC RETURNED NULL PTR *********");
    }


    show_alloc_mem();


    // free
    for (int k=0; k <= nb_iter; k++) {
        // printf("    ==== free operation n %d ====\n", k);
        ft_putstr("    ==== free operation n ");
        ft_iprint(k);
        ft_putendl(" ====");
        if (ptrs_test[k].str != NULL)
            do_free(ptrs_test[k].str);
    }

    // show_alloc_mem();

    // t_block *block;
    // t_area  *area;
    // for (int k=0; k < nb_iter; k++) {
    //     area = retrieve_area(ptrs_test[k].str);
    //     block = retrieve_block(area, ptrs_test[k].str);
    //     if (block == NULL)
    //         ft_putendl("block NULL");
    //     else {
    //         ft_putstr("block found :\nbusy : ");
    //         ft_iprint(block->busy);
    //         ft_putendl("");
    //         ft_putstr("size : ");
    //         ft_iprint(block->size);
    //         ft_putendl("");
    //     }
    // }

    return(0);

    // printf("\n========= Allocation 1 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 8);
    // str = (char *)malloc(sizeof(char) * 8);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str));
    // strncpy(str, tmp, 8);
    // printf("str : %s\n", str);


    // printf("\n========= Allocation 2 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 5);
    // str2 = (char *)malloc(sizeof(char) * 5);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str2));
    // strncpy(str2, tmp2, 10);
    // printf("str2 : %s\n", str2);

    // printf(RED "Free pointer str :" END "\n");
    // free(str);
    // printf(RED "Free pointer str2 :" END "\n");
    // free(str2);
    // return(0);
}