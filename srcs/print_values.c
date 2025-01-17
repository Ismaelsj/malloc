/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:24:48 by isidibe-          #+#    #+#             */
/*   Updated: 2020/10/14 16:12:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_umaxtoa_base(unsigned long long nb, int nb_base)
{
	long int	i;
	long int	j;
	int			end;
	char		str[1000000];
	char		*base;

	base = "0123456789abcdef";
	j = 1;
	i = nb;
	end = 0;
	while (i >= nb_base)
	{
		i /= nb_base;
		j++;
	}
	str[j--] = '\0';
	while (j >= end)
	{
		str[j] = base[nb % nb_base];
		nb /= nb_base;
		j--;
	}
	ft_putstr(str);
}

void		ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_iprint(int n)
{
	int a;

	if (n > 9)
	{
		a = n / 10;
		n -= 10 * a;
		ft_iprint(a);
	}
	ft_putchar('0' + n);
}

void		ft_putendl(char const *s)
{
	char	new_line;

	new_line = '\n';
	if (!s)
		return ;
	write(1, s, ft_strlen((char*)s));
	write(1, &new_line, 1);
}
