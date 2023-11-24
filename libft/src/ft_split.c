/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:29:21 by darismen          #+#    #+#             */
/*   Updated: 2023/11/24 20:37:31 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	*ft_free(char **newarry, size_t pos)
{
	while (pos != 0)
	{
		free(newarry[pos]);
		pos--;
	}
	free(newarry[pos]);
	free(newarry);
	return (NULL);
}

static void	ft_count_word(char const *s, size_t *first, size_t *last, char c)
{
	*first = *last;
	while (s[*first] == c)
		*first += 1;
	*last = *first;
	while (s[*last] != c && s[*last] != '\0')
		*last += 1;
}

static size_t	ft_count_splits(char const *s, char c)
{
	size_t		first;
	size_t		last;
	size_t		count;

	count = 0;
	first = 0;
	last = 0;
	while (s[last] != '\0')
	{
		ft_count_word(s, &first, &last, c);
		if (last == first)
			break ;
		else
			count++;
	}
	return (count);
}

static char	*ft_store_string(char const *str, size_t first, size_t last)
{
	char	*word;
	size_t	pos;
	size_t	len;

	pos = 0;
	len = last - first;
	word = malloc((sizeof(char)) * (len + 1));
	if (!word)
		return (NULL);
	word[len] = 0;
	while (first < last)
	{
		word[pos++] = str[first];
		first++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char		**newarry;
	size_t		first;
	size_t		last;
	size_t		pos;

	if (!s)
		return (NULL);
	newarry = (char **)malloc(((ft_count_splits(s, c)) + 1) * sizeof(char *));
	if (!newarry)
		return (NULL);
	newarry[ft_count_splits(s, c)] = 0;
	last = 0;
	first = 0;
	pos = 0;
	while (pos < ft_count_splits(s, c))
	{
		ft_count_word(s, &first, &last, c);
		if (last == first)
			break ;
		newarry[pos] = ft_store_string(s, first, last);
		if (!newarry[pos])
			return (ft_free(newarry, pos));
		pos++;
	}
	return (newarry);
}

/* Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer. */