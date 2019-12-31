/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <isidibe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:22:47 by IsMac             #+#    #+#             */
/*   Updated: 2019/12/31 11:27:01 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_bchr(void *s, int c, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)s;
	while (n > 0)
	{
		*d++ = c;
		n--;
	}
}

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

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (n--)
		*cs1++ = *cs2++;
	return (s1);
}

size_t	ft_strlen(char *str)
{
	char	*tmp;

	// ft_putendl("strlen : str NULL");
	if (!str) {
		return(0);
	}

	tmp = str;
	while (*str)
		str++;
	return (str - tmp);
}

void			ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

size_t			get_pool_size(int type) {

	if (type == TINY)
		return(TINY_BLOCK);
	else if (type == SMALL)
		return(SMALL_BLOCK);
	else
		return(0);
}

void 			ft_iprint(int n) {
    if( n > 9 )
      { int a = n / 10;

        n -= 10 * a;
        ft_iprint(a);
      }
    ft_putchar('0'+n);
}

void		ft_umaxtoa_base(unsigned long long nb, int nb_base)
{
	long int				i;
	long int				j;
	int						end;
	char					str[1000000];
	char					*base;

	base = "0123456789abcdef";
	j = 1;
	i = nb;
	end = 0;
	if (nb_base == 16) {
		str[0] = '0';
		str[1] = 'x';
		end = 2;
	}
	while (i >= nb_base)
	{
		i /= nb_base;
		j++;
	}
	// if (!(str = (char*)malloc(sizeof(char) * (j + 1))))
	// 	return (NULL);
	str[j--] = '\0';
	while (j >= end)
	{
		str[j] = base[nb % nb_base];
		nb /= nb_base;
		j--;
	}
	ft_putstr((char*)str);
	// return (str);
}


// // ----------------------------- crc32b --------------------------------

// url: https://stackoverflow.com/questions/21001659/crc32-algorithm-implementation-in-c-without-a-look-up-table-and-with-a-public-li

// /* This is the basic CRC-32 calculation with some optimization but no
// table lookup. The the byte reversal is avoided by shifting the crc reg
// right instead of left and by using a reversed 32-bit word to represent
// the polynomial.
//    When compiled to Cyclops with GCC, this function executes in 8 + 72n
// instructions, where n is the number of bytes in the input message. It
// should be doable in 4 + 61n instructions.
//    If the inner loop is strung out (approx. 5*8 = 40 instructions),
// it would take about 6 + 46n instructions. */

// unsigned int crc32b(unsigned char *message) {
unsigned int 	crc32(int *key, size_t len) {
   int j;
   unsigned int i;
   unsigned int byte;
   unsigned int crc;
   unsigned int mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (i < len) {
      byte = (unsigned int)key[i];            // Get next byte.
      crc = crc ^ byte;
	  j = 7;
      while (j >= 0) {    			// Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
		 j--;
      }
      i++;
   }
   return ~crc;
}

void	lock_block(t_block *block) {
	size_t len;

	len = sizeof(block) - sizeof(unsigned int);
	block->crc32 = crc32((void*)block+sizeof(unsigned int), len);
}

unsigned int	get_block_crc32(t_block *block) {
	size_t len;

	len = sizeof(block) - sizeof(unsigned int);
	return(crc32((void*)block+sizeof(unsigned int), len));
}

void	lock_area(t_area *area) {
	size_t len;

	len = sizeof(area) - sizeof(unsigned int);
	area->crc32 = crc32((void*)area+sizeof(unsigned int), len);
}

unsigned int	get_area_crc32(t_area *area) {
	size_t len;

	len = sizeof(area) - sizeof(unsigned int);
	return(crc32((void*)area+sizeof(unsigned int), len));
}

void	ft_putendl(char const *s)
{
	char	new_line;

	new_line = '\n';
	if (!s)
		return ;
	write(1, s, ft_strlen((char*)s));
	write(1, &new_line, 1);
}