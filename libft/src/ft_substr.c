/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:34:13 by darismen          #+#    #+#             */
/*   Updated: 2024/03/29 19:27:01 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	priv_substr_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

/**
 * @brief Creates a substring from a string
 * 
 * @param s 	input string
 * @param start	starting position
 * @param len 	lenght of substring
 * @return char* 
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (ft_strlen(s) < start || len == 0)
	{
		sub = (char *)ft_calloc(1, sizeof(char));
		if (!sub)
			return (NULL);
		return (sub);
	}
	if (ft_strlen(s) - start < len)
		len = (ft_strlen(s) - start);
	sub = (char *)ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	return (sub);
}

/**
 * @brief Creates a substring from a string
 * 
 * @param s 	input string
 * @param start	starting position
 * @param len 	lenght of substring
 * @return char* 
 */
/* char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	true_len;

	i = 0;
	true_len = priv_substr_strlen(s);
	if (start >= true_len)
	{
		subs = (char *)malloc(sizeof(char) * 1);
		subs[0] = '\0';
		return (subs);
	}
	if (true_len <= len)
		subs = (char *)malloc(sizeof(char) * (true_len + 1));
	else
		subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!(subs))
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		subs[i++] = s[start];
		start++;
	}
	subs[i] = '\0';
	return (subs);
} */

/* Reserva (con malloc(3)) y devuelve una substring de
la string ’s’.
La substring empieza desde el índice ’start’ y
tiene una longitud máxima ’len’. */