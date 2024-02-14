/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/02/14 17:24:22 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	ft_mini_exit(t_mini *data)
{
	clear_history();
	ft_env_lstclear(data->env_lst);
	exit(g_status);
}

int	echo(t_cmd	*cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_strncmp(cmd->c_args[1], "-n", 2))
	{
		flag = 1;
		i = 1;
	}
	while (cmd->c_args[++i])
	{
		ft_putstr_fd(cmd->c_args[i], 1);
		if (cmd->c_args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putendl_fd("", 0);
	return (0);
}
