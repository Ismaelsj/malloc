/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:22:47 by IsMac             #+#    #+#             */
/*   Updated: 2020/10/14 17:20:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_bzero(void *s, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)s;
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
}

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (n--)
		*cs1++ = *cs2++;
	return (s1);
}

size_t		ft_strlen(char *str)
{
	char	*tmp;

	if (!str)
	{
		return (0);
	}
	tmp = str;
	while (*str)
		str++;
	return (str - tmp);
}

int			choose_pool(size_t size)
{
	if (size <= TINY_BLOCK)
		return (TINY);
	else if (size <= SMALL_BLOCK)
		return (SMALL);
	else
		return (LARGE);
}

size_t		get_pool_size(int type)
{
	if (type == TINY)
		return (TINY_BLOCK);
	else if (type == SMALL)
		return (SMALL_BLOCK);
	else
		return (0);
}
