/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:22:47 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/03 16:53:15 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)s;
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
}

static size_t	ft_strlen(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str)
		str++;
	return (str - tmp);
}

void			ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

static int		len_num(unsigned long long value, int base)
{
	int		len;

	len = 0;
	while (value / base > 0)
	{
		value /= base;
		len++;
	}
	return (len + 1);
}

static void		put_base_core(unsigned long long value, int base, \
	int len)
{
	char	str[len];
	char	base_str[16] = "123456789abcdef";

	// base_str = "123456789abcdef";
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = base_str[value % base];
		value /= base;
		len--;
	}
	if (base == 16)
		ft_putstr("0x");
	ft_putstr(str);
}

void			put_base(unsigned long long value, int base)
{
	int		len;

	len = len_num(value, base);
	put_base_core(value, base, len);
}

t_area  *get_area(void *ptr) {

    t_area  *area;
    t_block *block;
    int     type;
    int     i;
    int     j;

    type = 0;
    i = 0;
    j = 0;
    while (type <= LARGE) {
        printf("searching in area of type %d\n", type);
        area = g_type[type].first_area;
        i = 0;
        while (area) {
            printf("searching in area n %d\n", i);
            block = area->first_block;
            j = 0;
            while (block) {
                printf("searching for block n %d\n", j);
                if (BLOCK_MEM(block) == ptr && block->busy == 1) {
                    printf("blockn n %d, found in area n %d, of type %d\n", j, i, type);
                    return(area);
                }
                block = block->next;
                j++;
            }
            area = area->next;
            i++;
        }
        type++;
    }
    return(NULL);
}