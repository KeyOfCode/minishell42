/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:50:54 by darismen          #+#    #+#             */
/*   Updated: 2023/11/22 20:19:07 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief DESCRIPTION
	 The strchr() function locates the first occurrence of c (converted to a
	 char) in the string pointed to by s.  The terminating null character is
	 considered to be part of the string; therefore if c is `\0', the func-
	 tions locate the terminating `\0'.

	 The strrchr() function is identical to strchr(), except it locates the
	 last occurrence of c.
 * 
 * @param str 
 * @param c 
 * @return The functions strchr() and strrchr() return a pointer to the located
	 character, or NULL if the character does not appear in the string.
 */
char	*ft_strrchr(const char *str, int c)
{
	int			i;

	c = (unsigned char)c;
	i = 0;
	while (str[i] != 0)
		i++;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i--;
	}
	return (0);
}

/* char	*ft_strrchr(const char *str, int c)
{
	int			i;
	const char	*start;

	c = (unsigned char)c;
	start = str;
	i = 0;
	while (str[i] != 0)
		i++;
	while (str[i] != *start && c != str[i])
		i--;
	if (c == str[i])
		return ((char *)&str[i]);
	else
		return (0);
}
*/

/* char	*ft_strrchr(const char *str, int c)
{
	int			i;
	const char	*start;

	c = (unsigned char)c;
	start = str;
	i = 0;
	while (str[i] != 0)
		i++;
	str = (str + i);
	while (*str != *start && c != *str)
		str--;
	if (c == *str)
		return ((char *)str);
	return (0);
} */

/*     char *strrchr(const char *s, int c);

DESCRIPTION
	 The strchr() function locates the first occurrence of c (converted to a
	 char) in the string pointed to by s.  The terminating null character is
	 considered to be part of the string; therefore if c is `\0', the func-
	 tions locate the terminating `\0'.

	 The strrchr() function is identical to strchr(), except it locates the
	 last occurrence of c.
	 
RETURN VALUES
	 The functions strchr() and strrchr() return a pointer to the located
	 character, or NULL if the character does not appear in the string.
	 */