/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/07 15:35:48 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    char *tmp = "Bonjour";
    char *tmp2 = "yahyahyah";
    char *str;
    char *str_bis;
    char *str2;
    char *str2_bis;
    char *str3;
    int  *tab;
    int  *tab2;

    // int i;
    // char *addr;

    // i = 0;
    // while(i < 1024) {
    //     addr = (char*)malloc(1024);
    //     addr[0] = 42;
    //     i++;
    // }
    // return(0);

    printf("\n========= Allocation 1 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 8);
    str = (char *)malloc(sizeof(char) * 8);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str));
    strncpy(str, tmp, 8);
    printf("str : %s\n", str);


    printf("\n========= Allocation 2 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 5);
    str2 = (char *)malloc(sizeof(char) * 5);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    strncpy(str2, tmp2, 14);
    printf("str2 : %s\n", str2);

    // printf(RED "\nFree pointer str2 :" END "\n");
    // free(str2);

    printf("\n========= Allocation 1 bis =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 8);
    str_bis = (char *)malloc(sizeof(char) * 8);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str_bis));
    strncpy(str_bis, tmp, 8);
    printf("str : %s\n", str_bis);

    printf("\n========= Allocation 3 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 60);
    str3 = (char *)malloc(sizeof(char) * 60);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str3));
    strncpy(str3, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    printf("str2 : %s\n", str3);

    return(0);

    // printf(RED "\nFree pointer str2 :" END "\n");
    // free(str2);

    printf("\n========= Reallocation 1 =========\n");
    str = (char *)realloc(str, sizeof(char) * 17);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    printf("str : %s\n", str);
    strncpy(str, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 16);
    printf("str : %s\n", str);


    printf(RED "\nFree pointer str2 :" END "\n");
    free(str);
    printf(RED "\nFree pointer str2 :" END "\n");
    free(str_bis);
    return(0);

    printf("\n========= Reallocation 2 =========\n");
    str2 = (char *)realloc(str2, sizeof(char) * 15);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    printf("str : %s\n", str2);
    strncpy(str2, "lalalalala lalal", 14);
    printf("str : %s\n", str2);

    // printf(RED "\nFree pointer str :" END "\n");
    // free(str);
    // printf(RED "\nFree pointer str2 :" END "\n");
    // free(str2);

    printf("\n========= Allocation 2 bis =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 18);
    str2_bis = (char *)malloc(sizeof(char) * 18);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2_bis));
    strncpy(str2_bis, tmp2, 14);
    printf("str2_bis : %s\n", str2_bis);


    printf(RED "\nFree pointer str_bis :" END "\n");
    free(str_bis);
    printf(RED "\nFree pointer str2_bis :" END "\n");
    free(str2_bis);


    // printf("\n========= Allocation 3 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(char) * 60);
    // str3 = (char *)malloc(sizeof(char) * 60);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(str3));
    // strncpy(str3, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    // printf("str2 : %s\n", str3);

    // printf("\n========= Allocation 4 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(int) * 1000);
    // tab = (int *)malloc(sizeof(int) * 1000);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(tab));
    // int i = 0;
    // while (i < 1000) {
    //     tab[i] = i;
    //     i++;
    // }
    // while (i > 900) {
    //     printf("tab[i] : %d\n", tab[i]);
    //     i--;
    // }
    // // printf("========= Allocation 4 =========\n");
    // // printf(" -- sizeof malloc : %lu\n", sizeof(int *) * 5000);
    // // tab2 = (int *)malloc(sizeof(int) * 5000);
    // // // printf("size of alocated string : %lu\n");
    // // printf("size of alocated string : %lu\n", sizeof(tab2));

    printf(RED "Free pointer str :" END "\n");
    free(str);
    printf(RED "Free pointer str2 :" END "\n");
    free(str2);
    // printf(RED "Free pointer tab :" END "\n");
    // free(tab);
    // printf(RED "Free pointer tab2 : %lu" END "\n", sizeof(tab2));
    // free(tab2);
    // printf(RED "Free pointer str3 : %lu" END "\n", sizeof(str3));
    // free(str3);
    // printf(GREEN "all done !" END "\n");
    // // while (1);
    return(0);
}