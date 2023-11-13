/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:56:46 by darismen          #+#    #+#             */
/*   Updated: 2022/11/05 13:29:02 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char c, va_list ap)
{
	int		add;

	add = 0;
	if (c == 'c')
		add += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		add += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		add += ft_putptr(va_arg(ap, void *));
	else if (c == 'i' || c == 'd')
		add += ft_putsigned(va_arg(ap, int));
	else if (c == 'u')
		add += ft_putnbr(BASE_DEC, va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		add += ft_puthex(va_arg(ap, unsigned int), c);
	else if (c == '%')
		add += ft_putchar(37);
	return (add);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format (str[i + 1], ap);
			i += 1;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (len);
}

/* int	main (void)
{
	int	t;

	t = 1234;
	printf (" %x\n %x\n %x\n", t, '0', "sdfhgsdfgsd");
	ft_printf(" %x\n %x\n %x\n", t, '0', "sdfhgsdfgsd");
	printf("\n");
}
 */
