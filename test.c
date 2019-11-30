/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:55:19 by IsMac             #+#    #+#             */
/*   Updated: 2019/11/30 13:58:10 by isidibe-         ###   ########.fr       */
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

    // printf("%d %d %d\n", (32 + 16) & ~16, (200 + 16) & ~16, (3 + 16) & ~16);
    // return(0);
    printf("========= Allocation 1 =========");
    printf(" -- sizeof malloc : %lu\n", sizeof(char *) * 8);
    str = (char *)malloc(sizeof(char *) * 8);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str));
    strncpy(str, tmp, 8);
    printf("str : %s\n", str);

    printf("========= Allocation 2 =========");
    printf(" -- sizeof malloc : %lu\n", sizeof(char *) * 10);
    str2 = (char *)malloc(sizeof(char *) * 10);
    // printf("size of alocated string : %lu\n");
    printf("size of alocated string : %lu\n", sizeof(str2));
    strncpy(str2, tmp2, 14);
    printf("str2 : %s\n", str2);

    printf("Free pointer str :\n");
    ft_free(str);
    printf("Free pointer str2 :\n");
    ft_free(str2);
    printf("all done !\n");
    return(0);
}