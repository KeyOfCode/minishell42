/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:06:56 by darismen          #+#    #+#             */
/*   Updated: 2024/03/15 18:49:03 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

int	ft_putnbr_base_fd(char *base, unsigned long long n, int fd)
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
	len += ft_putstr_fd(num, fd);
	len++;
	free(num);
	return (len);
}
