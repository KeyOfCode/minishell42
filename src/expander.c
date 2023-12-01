/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/01 18:53:39 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_env(const char *search, char **env)
{
	int		search_len;
	char	*expanded;
	int		i;

	if (!search || !env)
		return (NULL);
	if (search[0] == '~' && ft_strlen(search) == 1)
		search = "$HOME";
	search++;
	search_len = ft_strlen(search);
	expanded = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp((const char *)env[i], search, search_len) == 0)
		{
			if (env[i][search_len] == '=' || env[i][search_len] == '\0')
			{
				expanded = env[i] + search_len + 1;
				break ;
			}
		}
		i++;
	}
	return (expanded);
}

void	ft_expander(t_mini *data)
{
	char	*expanded;
	char	**cmd;
	char	**env;
	int		i;
	int		j;

	i = 0;
	while (data->full_cmd[i])
	{
		if (data->full_cmd[i][0] != '\'')
		{
			j = 1;
			if (ft_strchr("$~", data->full_cmd[i][j]))
				expanded = expand_env(data->full_cmd[i], data->envp);
			j++;
		}
		i++;
	}
}
