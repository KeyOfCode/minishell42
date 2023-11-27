/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/11/27 19:45:50 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_search_env(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != '$' || line[i] != '~'))
	{
		i++;
	}
	if (line[i] == '$')
		get_env(0);
	if (line[i] == '~')
		get_full_path(0);
}

void	ft_expander(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\"')
			ft_search_env(cmd[i]);
		else if (cmd[i][0] == '$')
			get_env(0);
		else if (cmd[i][0] == '~')
			get_full_path(0);
		i++;
	}
}
