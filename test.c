/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/21 16:23:02 by IsMac            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

char    *do_malloc(char *null, size_t size) {
    
    char    *str;

    (void*)null;
    // printf(GREEN "========= Mallocation =========\n");
    printf("size : %lu\n", size);
    if ((str = (char *)malloc(sizeof(char) * size)) == NULL) {
        printf("NULL returned\n\n");
        return(0);
    }
    ft_bchr(str, 'm', size-1);
    printf(GREEN "malloc has succeeded\n\n" END, str);
    return(str);
}

char    *do_realloc(char *str, size_t size) {
    // printf(YELLOW "========= Reallocation =========\n");
    if (str == NULL)
        return(NULL);
    printf("from size : %lu, to size : %lu\n", ft_strlen(str), size);
    printf("size : %lu\n", size);
    if ((str = (char *)realloc(str, sizeof(char) * size)) == NULL) {
        printf("NULL returned\n\n");
        return(0);
    }
    ft_bchr(str, 'r', size-1);
    printf(GREEN "realloc has succeeded\n\n" END);
    return(str);
}

char    *do_free(char *str, size_t n) {
    // printf(YELLOW "========= Free =========\n");
    free(str);
    printf(GREEN "pointer str freed\n\n" END);
    return(NULL);
}

typedef char* (*fptr)(char*, size_t);

typedef struct		s_test_ptr
{
    char            *str;
}	                t_test_ptr;

int main(void) {

    // char *tmp = "Bonjour";
    // char *tmp2 = "yahyahyah aifu ruhseru hweur hewger reg reugweur giwoeubrguberwub goeurybgouyrb oeuyrbg";
    // char *str;
    // char *str_bis;
    // char *str2;
    // char *str2_bis;
    // char *str3;
    // char *str4;
    // int  *tab;
    // int  *tab2;

    // int i;
    // char *addr;

    // i = 0;
    // while(i < 1024) {
    //     addr = (char*)malloc(1024);
    //     addr[0] = 42;
    //     i++;
    // }
    // return(0);

    t_test_ptr  ptrs_test[100];
    fptr        ftab[3] = {&do_malloc, &do_realloc, &do_free};
    int         nb_action = 100;
    int         lower_ptr = 0, upper_ptr = 999;
    int         lower_act = 0, upper_act = 2;
    int         nb_iter = 99;
    
    // init ptr to NULL
    for (int i=0; i < nb_iter; i++) {
        ptrs_test[i].str = NULL;
    }

    // // random operations
    // for (int j = 0; j < nb_action; j++) {
    //     printf("-- operation n %d --\n", j);
    //     int ptr_index = (rand() % (upper_ptr - lower_ptr + 1)) + lower_ptr; 
    //     int act_index = (rand() % (upper_act - lower_act + 1)) + lower_act; 
    //     int size = (rand() % (99999 - 4 + 1)) + 4; 
    //     ptrs_test[ptr_index].str = ftab[act_index](ptrs_test[ptr_index].str, size);
    // }

    // malloc
    for (int k=0; k < nb_iter; k++) {
        printf("    ==== malloc operation n %d ====\n", k);
        size_t size = (rand() % (5000 - 4 + 1)) + 4; 
        ptrs_test[k].str = do_malloc(ptrs_test[k].str, size);
    }

    // random free
    for (int k=0; k < (nb_iter - 50); k++) {
        printf("    ==== random free operation n %d ====\n", k);
        size_t ptr = (rand() % (99 - 0 + 1)) + 0;
        if (ptrs_test[ptr].str != NULL)
            do_free(ptrs_test[ptr].str, 0);
    }

    // realloc
    for (int k=0; k < (nb_iter - 50); k++) {
        printf("    ==== realloc operation n %d ====\n", k);
        size_t size = (rand() % (5000 - 4 + 1)) + 4;
        size_t ptr = (rand() % (99 - 0 + 1)) + 0;
        ptrs_test[ptr].str = do_realloc(ptrs_test[k].str, size);
    }

    // free
    for (int k=0; k <= nb_iter; k++) {
        printf("    ==== free operation n %d ====\n", k);
        if (ptrs_test[k].str != NULL)
            do_free(ptrs_test[k].str, 0);
    }
    return(0);

    // printf("sizeof t_block : %lu\n", sizeof(t_block));

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

    // // printf(RED "\nFree pointer str2 :" END "\n");
    // // free(str2);

    // printf("\n========= Allocation 1 bis =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 8);
    // str_bis = (char *)malloc(sizeof(char) * 8);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str_bis));
    // strncpy(str_bis, tmp, 8);
    // printf("str : %s\n", str_bis);

    // printf("str2 : %s\n", str2);
    // strncpy(str2, tmp2, 15);
    // printf("str2 : %s\n", str2);

    // printf("\n========= Allocation 3 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 60);

    // if ((str3 = (char *)malloc(sizeof(char) * 60)) == NULL) {
    //     printf("allocation failed !\n");
    //     return(0);
    // }
    // // printf("size of alocated string : %lu\n");
    // else {
    //     printf("size of alocated string : %lu\n", sizeof(str3));
    //     strncpy(str3, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    //     printf("str2 : %s\n", str3);
    // }

    // printf("\n========= Allocation 4 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 60);
    // str4 = (char *)malloc(sizeof(char) * 60);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str4));
    // strncpy(str4, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    // printf("str2 : %s\n", str4);

    // return(0);

    // // printf(RED "\nFree pointer str2 :" END "\n");
    // // free(str2);

    // printf("\n========= Reallocation 1 =========\n");
    // str = (char *)realloc(str, sizeof(char) * 17);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str2));
    // printf("str : %s\n", str);
    // strncpy(str, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 16);
    // printf("str : %s\n", str);


    // printf(RED "\nFree pointer str2 :" END "\n");
    // free(str);
    // printf(RED "\nFree pointer str2 :" END "\n");
    // free(str_bis);
    // return(0);

    // printf("\n========= Reallocation 2 =========\n");
    // str2 = (char *)realloc(str2, sizeof(char) * 15);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str2));
    // printf("str : %s\n", str2);
    // strncpy(str2, "lalalalala lalal", 14);
    // printf("str : %s\n", str2);

    // // printf(RED "\nFree pointer str :" END "\n");
    // // free(str);
    // // printf(RED "\nFree pointer str2 :" END "\n");
    // // free(str2);

    // printf("\n========= Allocation 2 bis =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 18);
    // str2_bis = (char *)malloc(sizeof(char) * 18);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str2_bis));
    // strncpy(str2_bis, tmp2, 14);
    // printf("str2_bis : %s\n", str2_bis);

    // printf("========= Allocation 4 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(int *) * 5000);
    // tab2 = (int *)malloc(sizeof(int) * 5000);
    // printf("size of alocated string : %lu\n", sizeof(tab2));


    // printf(RED "\nFree pointer str_bis :" END "\n");
    // free(str_bis);
    // printf(RED "\nFree pointer str2_bis :" END "\n");
    // free(str2_bis);


    // // printf("\n========= Allocation 3 =========\n");
    // // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 60);
    // // str3 = (char *)malloc(sizeof(char) * 60);
    // // // printf("size of alocated string : %lu\n");
    // // printf("size of alocated string : %lu\n", sizeof(str3));
    // // strncpy(str3, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    // // printf("str2 : %s\n", str3);

    // // printf("\n========= Allocation 4 =========\n");
    // // printf(" -- sizeof malloc : %lu\n", sizeof(int) * 1000);
    // // tab = (int *)malloc(sizeof(int) * 1000);
    // // // printf("size of alocated string : %lu\n");
    // // printf("size of alocated string : %lu\n", sizeof(tab));
    // // int i = 0;
    // // while (i < 1000) {
    // //     tab[i] = i;
    // //     i++;
    // // }
    // // while (i > 900) {
    // //     printf("tab[i] : %d\n", tab[i]);
    // //     i--;
    // // }
    // // // printf("========= Allocation 4 =========\n");
    // // // printf(" -- sizeof malloc : %lu\n", sizeof(int *) * 5000);
    // // // tab2 = (int *)malloc(sizeof(int) * 5000);
    // // // // printf("size of alocated string : %lu\n");
    // // // printf("size of alocated string : %lu\n", sizeof(tab2));

    // printf(RED "Free pointer str :" END "\n");
    // free(str);
    // printf(RED "Free pointer str2 :" END "\n");
    // free(str2);
    // // printf(RED "Free pointer tab :" END "\n");
    // // free(tab);
    // // printf(RED "Free pointer tab2 : %lu" END "\n", sizeof(tab2));
    // // free(tab2);
    // // printf(RED "Free pointer str3 : %lu" END "\n", sizeof(str3));
    // // free(str3);
    // // printf(GREEN "all done !" END "\n");
    // // // while (1);
    // return(0);
}