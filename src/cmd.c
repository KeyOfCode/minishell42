/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/29 15:23:04 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_fillcmd(char **args)
{
	t_cmd	*newcmd;
}

void	ft_cmdlst(t_mini *data)
{
	t_cmd	*newcmd;
	int		count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	while (data->full_cmd[i])
		if (data->full_cmd[i++] == "|")
			count++;
	i = 0;
	newcmd = ft_fillcmd(&data->full_cmd[i]);
	while (data->full_cmd[i] && data->full_cmd[i] != "|")
	{
		newcmd->c_args[i] = data->full_cmd[i];
	}
	newcmd->c_abs_path = newcmd->c_abs_path[0];
	if (count == 0)
		data->cmd_list[0] = *newcmd;
	else
		while (i < count)
			data->cmd_list[i++] = *newcmd;
}
