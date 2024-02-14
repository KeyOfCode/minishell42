/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/02/14 19:16:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_mini_exit(t_mini *data)
{
	ft_env_lstclear(data->env_lst);
	exit(EXIT_SUCCESS);
}

void	echo(t_cmd	*cmd)
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
}

void	cd(t_mini *data, t_cmd *cmd)
{
	if (!cmd->c_args[1] || !ft_strncmp(cmd->c_args[1], "~", 1))
		cmd->c_args[1] = get_env(data, "HOME");
	else if (!ft_strncmp(cmd->c_args[1], "-", 1))
	{
		if (!get_env(data, "OLDPWD"))
		{
			ft_error("bash: cd: OLDPWD not set");
			return ;
		}
		else
		{
			cmd->c_args[1] = get_env(data, "OLDPWD");
			printf("%s\n", cmd->c_args[1]);
		}
	}
	if (!opendir(cmd->c_args[1]))
		ft_error("bash: cd: %s: No such file or directory");
	set_env(data, "OLDPWD", getcwd(NULL, 0));
	chdir(cmd->c_args[1]);
	set_env(data, "PWD", getcwd(NULL, 0));
}
