/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:05:13 by darismen          #+#    #+#             */
/*   Updated: 2022/09/21 13:21:41 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, unsigned int len)
{
	unsigned int	n;
	void			*og_dest;

	og_dest = dest;
	if (!dest && !src)
		return (0);
	n = 0;
	if ((unsigned int)dest - (unsigned int)src < len)
	{
		n = len - 1;
		while (n < len)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
			n--;
		}
	}
	else
	{
		while (n < len)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
			n++;
		}
	}
	return (og_dest);
}

/*
** LIBRARY: <string.h>
** SYNOPSIS: copy byte string
**
** DESCRIPTION:
** 		The memmove() function copies n bytes from string s2 to string s1.  The
**	two strings may overlap; the copy is always done in a non-destructive
**	manner.
	RETURN VALUES
     	The memmove() function returns the original value of dst.
*/