/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:03:55 by isidibe-          #+#    #+#             */
/*   Updated: 2020/01/03 11:18:01 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int     main(void) {

    int fd;
    char buf[20];
    ssize_t i;

    fd = open("run.sh", O_RDONLY);
    i = read(fd, buf, 19);
    printf("%lu bytes : %s\n", i, buf);

    return(0);
}