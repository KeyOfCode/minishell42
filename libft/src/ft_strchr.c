/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:50:05 by darismen          #+#    #+#             */
/*   Updated: 2022/09/27 16:07:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != '\0' && c != *s)
		s++;
	if (c == *s)
		return ((char *)s);
	return (0);
}

/* SYNOPSIS
     #include <string.h>

     char *
     strchr(const char *s, int c);

DESCRIPTION
     The strchr() function locates the first occurrence of c 
	 (converted to a char) in the string pointed to by s.  
	 The terminating null character is considered to be part of 
	 the string; therefore if c is `\0', the functions locate 
	 the terminating `\0'.

     The strrchr() function is identical to strchr(), 
	 except it locates the last occurrence of c.

RETURN VALUES
     The functions strchr() and strrchr() return a pointer to 
	 the located character, or NULL if the character does not 
	 appear in the string. 
	 */