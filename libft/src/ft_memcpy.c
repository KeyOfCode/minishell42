/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:56:37 by darismen          #+#    #+#             */
/*   Updated: 2022/11/28 17:10:50 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned int	n;
	void			*og_dest;

	og_dest = dest;
	n = 0;
	if (!dest && !src)
		return (NULL);
	while (n < size)
	{
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		n++;
	}
	return (og_dest);
}
