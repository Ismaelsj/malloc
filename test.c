/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/02 14:32:43 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

int main(void) {

    char *tmp = "Bonjour";
    char *tmp2 = "yahyahyah";
    char *str;
    char *str2;
    char *str3;
    int  *tab;
    int  *tab2;
    // return(0);

    printf("pagesize : %d\n", getpagesize());
    // return(0);
    printf("\n========= Allocation 1 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 8);
    str = (char *)malloc(sizeof(char) * 8);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str));
    strncpy(str, tmp, 8);
    printf("str : %s\n", str);

    printf("\n========= Allocation 2 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char) * 10);
    str2 = (char *)malloc(sizeof(char) * 10);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    strncpy(str2, tmp2, 14);
    printf("str2 : %s\n", str2);

    printf("\n========= Allocation 3 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char*) * 60);
    str3 = (char *)malloc(sizeof(char*) * 60);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str3));
    strncpy(str3, "Chaque zone doit pouvoir contenir au moins 100 allocations.", 59);
    printf("str2 : %s\n", str3);

    printf("\n========= Allocation 4 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(int) * 1000);
    tab = (int *)malloc(sizeof(int) * 1000);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(tab));
    int i = 0;
    while (i < 1000) {
        tab[i] = i;
        i++;
    }
    while (i > 900) {
        printf("tab[i] : %d\n", tab[i]);
        i--;
    }
    // printf("========= Allocation 4 =========\n");
    // printf(" -- sizeof malloc : %lu\n", sizeof(int *) * 5000);
    // tab2 = (int *)malloc(sizeof(int) * 5000);
    // // printf("size of alocated string : %lu\n");
    // printf("size of alocated string : %lu\n", sizeof(tab2));

    printf(RED "Free pointer str :" END "\n");
    ft_free(str);
    printf(RED "Free pointer str2 :" END "\n");
    ft_free(str2);
    printf(RED "Free pointer tab :" END "\n");
    ft_free(tab);
    printf(RED "Free pointer tab2 : %lu" END "\n", sizeof(tab2));
    ft_free(tab2);
    printf(RED "Free pointer str3 : %lu" END "\n", sizeof(str3));
    ft_free(str3);
    printf(GREEN "all done !" END "\n");
    // while (1);
    return(0);
}