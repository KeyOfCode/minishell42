/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:11:19 by darismen          #+#    #+#             */
/*   Updated: 2024/03/19 15:02:50 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*priv_memset(void *b, int c, unsigned int len)
{
	unsigned long	i;

	i = 0;
	c = (unsigned char)c;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

void	*ft_calloc(unsigned int count, unsigned int size)
{
	unsigned int	tot_size;
	void			*dst;

	tot_size = size * count;
	dst = malloc(tot_size);
	if (!(dst))
		return (0);
	priv_memset(dst, 0, tot_size);
	return (dst);
}

/* The calloc() function contiguously 
	allocates enough space for count objects that 
	are size bytes of memory each and returns a pointer 
	to the allocated memory. The allocated memory is
	filled with bytes of value zero. */