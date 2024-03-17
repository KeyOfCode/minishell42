/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:56:46 by darismen          #+#    #+#             */
/*   Updated: 2024/03/15 14:35:37 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(int fd, char c, va_list ap)
{
	int		add;

	add = 0;
	if (c == 'c')
		add += ft_putchar_fd(va_arg(ap, int), fd);
	else if (c == 's')
		add += ft_putstr_fd(va_arg(ap, char *), fd);
	else if (c == 'p')
		add += ft_putptr_fd(va_arg(ap, void *), fd);
	else if (c == 'i' || c == 'd')
		add += ft_putsigned_fd(va_arg(ap, int), fd);
	else if (c == 'u')
		add += ft_putnbr_base_fd(BASE_DEC, va_arg(ap, unsigned int), fd);
	else if (c == 'x' || c == 'X')
		add += ft_puthex_fd(va_arg(ap, unsigned int), c, fd);
	else if (c == '%')
		add += ft_putchar_fd(37, fd);
	return (add);
}

int	ft_printf_fd(int fd, char const *str, ...);

int	ft_printf(char const *str, va_list args)
{
	int	len;

	len = ft_printf_fd(1, str, args);
	return (len);
}

int	ft_printf_fd(int fd, char const *str, ...)
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
			len += ft_format(fd, str[i + 1], ap);
			i += 1;
		}
		else
			len += ft_putchar_fd(str[i], fd);
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
