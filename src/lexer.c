/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/11/27 21:01:40 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * @note First IF checks: ???
 * @note Second IF checks if it's << or <
 * 
 */
void	ft_spchar(char *str, size_t *i, size_t *size, char *spc)
{
	if (str[*i] && !ft_strchr(spc, str[*i - 1]))
		(*size)++;
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
		(*i) += 2;
	else
		(*i)++;
}

int	ft_quotes(char *s, size_t i, char q)
{
	int	j;

	j = i + 1;
	while (s[j] != '\0' && s[j] != q)
		j++;
	if (s[j] == q)
	{
		i++;
		while (s[i] != q && s[i] != '\0')
			i++;
		return (i);
	}
	else
	{
		ft_error("Unclosed quote error");
		return (0);
	}
}

size_t	ft_count_splits(char *str, size_t size, char *spc)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_strchr(spc, str[i]))
			i++;
		if (str[i])
			size++;
		while (str[i] != ' ' && str[i] != '\0')
		{
			if (str[i] == '\"')
				i = ft_quotes(str, i, '\"');
			else if (str[i] == '\'')
				i = ft_quotes(str, i, '\'');
			else if (ft_strchr("|<>", str[i]))
				ft_spchar(str, &i, &size, "|<>");
			i++;
		}
	}
	return (size);
}

/**
 * @note I still can't store only the spcharacters, fix later.
 */
char	*ft_store_string(char *s, char *spc, size_t *pos)
{
	size_t			i;
	size_t			j;
	char			*str;

	i = *pos;
	while (ft_strchr(spc, s[i]) && s[i])
		i++;
	j = i;
	while (s[i] != ' ' && s[i] != '\0')
	{
		if (s[i] == '\"')
			i = ft_quotes(s, i, '\"');
		else if (s[i] == '\'')
			i = ft_quotes(s, i, '\'');
		else if (ft_strchr("|<>", str[i]))
			ft_spchar(str, &i, &pos, "|<>");
		i++;
	}
	if (i > j)
	{
		str = ft_strndup(&s[j], i - j);
		*pos = i;
		return (str);
	}
	return (0);
}

char	**ft_cmdtrim(char *s)
{
	size_t	size;
	size_t	i;
	size_t	pos;
	char	**out;

	size = 0;
	size = ft_count_splits(s, size, " |<>");
	printf("nº tokens: %zu\n", size);
	out = (char **)malloc(sizeof(char *) * (size + 1));
	if (!s || !out)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < size)
	{
		out[i] = ft_store_string(s, " |<>", &pos);
		i++;
	}
	out[i] = NULL;
	return (out);
}

/* char	**ft_cmdtrim(char *s)
{
	char		**newarry;
	size_t		first;
	size_t		last;
	size_t		pos;

	if (!s)
		return (NULL);
	newarry = (char **)malloc(((ft_count_splits(s, ' ')) + 1) * sizeof(char *));
	if (!newarry)
		return (NULL);
	newarry[ft_count_splits(s, ' ')] = 0;
	last = 0;
	first = 0;
	pos = 0;
	while (pos < ft_count_splits(s, ' '))
	{
		ft_count_word(s, &first, &last, ' ');
		if (last == first)
			break ;
		newarry[pos] = ft_store_string(s, first, last);
		if (!newarry[pos])
			return (ft_free(newarry, pos));
		pos++;
	}
	return (newarry);
} */

/* char	**ft_split(char *str)
{
	int i = 0, j = 0, k = 0, wc = 0;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	char **out = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
} */

/* static char	*ft_store_string(char const *str, size_t first, size_t last)
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
} */
