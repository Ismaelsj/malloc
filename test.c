/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2019/11/30 14:58:47 by isidibe-         ###   ########.fr       */
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
    int  *tab;

    // printf("%d %d %d\n", (32 + 16) & ~16, (200 + 16) & ~16, (3 + 16) & ~16);
    // return(0);
    printf("========= Allocation 1 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char *) * 8);
    str = (char *)malloc(sizeof(char *) * 8);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str));
    strncpy(str, tmp, 8);
    printf("str : %s\n", str);

    printf("========= Allocation 2 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(char *) * 10);
    str2 = (char *)malloc(sizeof(char *) * 10);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    strncpy(str2, tmp2, 14);
    printf("str2 : %s\n", str2);

    printf("========= Allocation 3 =========\n");
    printf(" -- sizeof malloc : %lu\n", sizeof(int *) * 1000);
    tab = (int *)malloc(sizeof(int *) * 1000);
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

    printf("Free pointer str :\n");
    ft_free(str);
    printf("Free pointer str2 :\n");
    ft_free(str2);
    printf("Free pointer tab :\n");
    ft_free(tab);
    printf("all done !\n");
    return(0);
}