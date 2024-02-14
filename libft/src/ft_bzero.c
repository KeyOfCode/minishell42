/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:51:05 by darismen          #+#    #+#             */
/*   Updated: 2022/09/21 14:21:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}	
}

/*
** LIBRARY: <strings.h>
** SYNOPSIS: write zeroes to a byte string
**
** DESCRIPTION:
** 		The bzero() function writes n zeroed bytes to the string s. If n is
**	zero, bzero() does nothing.
*/

/* void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
} */