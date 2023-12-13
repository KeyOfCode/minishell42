/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/08 20:05:04 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * @note #First IF checks if the previous character is not a special character
 * @note #Second IF checks if it's << or <
 * 
 */
void	ft_spchar(char *str, size_t *i, size_t *size, int mode)
{
	if (!mode)
	{
		if (str[*i] && !ft_strchr(" |<>", str[*i - 1]))
			(*size)++;
		if ((str[*i] == '<' && str[*i + 1] == '<')
			|| (str[*i] == '>' && str[*i + 1] == '>'))
			(*i) += 2;
		else
			(*i)++;
	}
	else
	{
		if ((str[*i] == '<' && str[*i + 1] == '<')
			|| (str[*i] == '>' && str[*i + 1] == '>'))
			(*i) += 2;
		else
			(*i)++;
	}
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

size_t	ft_count_splits(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			size++;
		while (!ft_strchr(" |<>", str[i]) && str[i] != '\0')
		{
			if (str[i] == '\"')
				i = ft_quotes(str, i, '\"');
			else if (str[i] == '\'')
				i = ft_quotes(str, i, '\'');
			i++;
		}
		if (ft_strchr("|<>", str[i]) && str[i] != '\0')
			ft_spchar(str, &i, &size, 0);
	}
	return (size);
}

/**
 * @note 
 */
char	*ft_store_string(char *str, size_t *pos)
{
	size_t	i;
	size_t	j;

	i = *pos;
	while (str[i] == ' ' && str[i])
		i++;
	j = i;
	if (!ft_strchr(" |<>", str[i]) && str[i] != '\0')
	{
		while (!ft_strchr(" |<>", str[i]) && str[i] != '\0')
		{
			if (str[i] == '\"')
				i = ft_quotes(str, i, '\"');
			else if (str[i] == '\'')
				i = ft_quotes(str, i, '\'');
			i++;
		}
	}
	else
		ft_spchar(str, &i, pos, 1);
	if (i > j)
		*pos = i;
	return (ft_strndup(&str[j], i - j));
}
	/* printf("i: %zu\t j: %zu\n", i, j);
	printf("&str[j]: %s\n", &str[j]);
	printf("i - j: %zu\n", i - j);
	printf("%s\n", newstr); 
	*/

char	**ft_cmdtrim(char *s)
{
	size_t	size;
	size_t	i;
	size_t	pos;
	char	**out;

	size = 0;
	size = ft_count_splits(s, size);
	out = (char **)malloc(sizeof(char *) * (size + 1));
	if (!s || !out)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < size)
	{
		out[i] = ft_store_string(s, &pos);
		i++;
	}
	out[i] = NULL;
	return (out);
}
/* 	printf("nº tokens: %zu\n", size);
	printf("#:%s\n\n", out[i]); */