/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:09:48 by darismen          #+#    #+#             */
/*   Updated: 2022/10/19 12:29:44 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	len_int(int value)
{
	int	l;

	l = 0;
	if (value == 0)
		l = 1;
	if (value < 0)
	{
		value *= -1;
		l++;
	}
	while (value)
	{
		value /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*nb;
	long	num;
	int		len;
	int		i;

	num = (long)n;
	len = len_int(num);
	i = len;
	nb = (char *)malloc(sizeof(char) * (len + 1));
	if (!(nb))
		return (NULL);
	if (num == 0)
		nb[0] = '0';
	if (num < 0)
	{
		nb[0] = '-';
		num *= -1;
	}
	while (i-- > 0 && num != 0)
	{
		nb[i] = (num % 10) + '0';
		num /= 10;
	}
	nb[len] = '\0';
	return (nb);
}

/* Descripción 
	Utilizando malloc(3), genera una string que
	represente el valor entero recibido como argumento.
	Los números negativos tienen que gestionarse. */

/* #include <stdlib.h>
#include <unistd.h>

void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}
 */
/* int	main(void)
{
	char *res;

	res = ft_itoa(9);
	ft_print_result(res);
	free(res);
} */

/* int		main(int argc, const char *argv[])
{
	int		arg;

	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		char *res = ft_itoa(0);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 2)
	{
		char *res = ft_itoa(9);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 3)
	{
		char *res = ft_itoa(-9);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 4)
	{
		char *res = ft_itoa(10);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 5)
	{
		char *res = ft_itoa(-10);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 6)
	{
		char *res = ft_itoa(8124);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 7)
	{
		char *res = ft_itoa(-9874);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 8)
	{
		char *res = ft_itoa(543000);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 9)
	{
		char *res = ft_itoa(-2147483648LL);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 10)
	{
		char *res = ft_itoa(2147483647);
		ft_print_result(res);
		free(res);
	}
	else if (arg == 11)
	{
		char *res = ft_itoa(-2147483647);
		ft_print_result(res);
		free(res);
	}
	return (0);
} */