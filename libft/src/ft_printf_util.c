/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:36:33 by darismen          #+#    #+#             */
/*   Updated: 2022/11/05 13:31:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_num_len(unsigned long value, char *base)
{
	int	l;

	l = 0;
	if (value == 0)
		l = 1;
	while (value)
	{
		value /= (unsigned long)ft_strlen(base);
		l++;
	}
	return (l);
}

int	ft_puthex(unsigned int n, char cap)
{
	int		count;
	char	*base;

	count = 0;
	if (cap == 'X')
		base = MAY_BASE_HEX;
	else
		base = BASE_HEX;
	count += ft_putnbr(base, n);
	return (count);
}

int	ft_putsigned(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr("-2");
		n = 147483648;
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n *= -1;
	}
	count += ft_putnbr(BASE_DEC, n);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int		count;

	count = 0;
	ft_putstr("0x");
	count += 2;
	count += ft_putnbr(BASE_HEX, (unsigned long long)ptr);
	return (count);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}
