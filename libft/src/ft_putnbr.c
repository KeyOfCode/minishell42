/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:06:56 by darismen          #+#    #+#             */
/*   Updated: 2024/03/13 18:43:53 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(char *base, unsigned long long n)
{
	int		len;
	int		bsize;
	char	*num;

	len = ft_num_len(n, base);
	bsize = ft_strlen(base);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!(num))
		return (0);
	num[len] = '\0';
	while (len-- > 0)
	{
		num[len] = (base[(n % bsize)]);
		n /= bsize;
	}
	len += ft_putstr(num);
	len++;
	free(num);
	return (len);
}
