/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/04/02 13:59:28 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Currently doesn't considers if the env doesn't have a =
 * 
 * @param str 
 * @param envp 
 * @param i 	Pointer to the counter in ft_subdivide so I can count
 * over the env. Because it's a pointer, I don't need to return it.
 * @return char* 
 */
char	*ft_env_expand(char *ogstr, t_mini *data, int *i)
{
	t_env	*head;
	char	*str;

	head = data->env_lst;
	str = ogstr;
	if (str[0] == '~')
		str = "$HOME";
	while (head)
	{
		if (ft_strncmp(&str[1], head->nm, ft_strlen(head->nm)) == 0)
		{
			if (ogstr[0] != '~')
				*i += ft_strlen(head->nm);
			else
				*i += 1;
			return (ft_strdup(head->val));
		}
		head = head->next;
	}
	if (ft_strchr("?", str[1]))
		return ((*i) += 1, ft_itoa(g_status));
	while (*(++str) != '\0' && *str != '$')
		*i += 1;
	return (ft_strdup(""));
}

char	*ft_substr_expand(char *str, t_mini *data)
{
	int		i;
	int		j;
	char	*full;

	i = 0;
	full = ft_strdup("\0");
	if (str[0] == '~')
		full = ft_join_free(full, ft_env_expand(str, data, &i), 2);
	j = i;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			data->dquote = (data->dquote + 1) % 2;
		if (str[i] == '\'' && data->dquote == 0)
			i = ft_quotes(str, i, '\'');
		if (str[i] == '$' && str[i + 1])
		{
			full = ft_join_free(full, ft_substr(str, j, i - j), 2);
			full = ft_join_free(full, ft_env_expand(&str[i], data, &i), 2);
			j = i + 1;
		}
		i++;
	}
	full = ft_join_free(full, ft_substr(str, j, i - j), 2);
	return (free(str), full);
}

int	ft_flag(char str, t_mini *data, int *rm_dq, int *rm_sq)
{
	if (str == '\"' && data->squote == 0)
	{
		data->dquote = (data->dquote + 1) % 2;
		(*rm_dq)++;
		return (0);
	}
	if (str == '\'' && data->dquote == 0)
	{
		data->squote = (data->squote + 1) % 2;
		(*rm_sq)++;
		return (0);
	}
	else
		return (1);
}

char	*ft_quotes_rmv(t_mini *data, char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		rm_dq;
	int		rm_sq;

	i = 0;
	rm_dq = 0;
	rm_sq = 0;
	if (!str)
		return (NULL);
	while (str[i])
		ft_flag(str[i++], data, &rm_dq, &rm_sq);
	newstr = ft_calloc((ft_strlen(str) - rm_dq - rm_sq + 1), sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_flag(str[i], data, &rm_dq, &rm_sq))
			newstr[j++] = str[i];
		i++;
	}
	free(str);
	return (data->dquote = 0, data->squote = 0, newstr);
}

void	ft_expander(t_mini *data)
{
	int		i;

	i = 0;
	while (data->full_cmd[i])
	{
		data->full_cmd[i] = ft_substr_expand(data->full_cmd[i], data);
		data->full_cmd[i] = ft_quotes_rmv(data, data->full_cmd[i]);
		i++;
	}
}
