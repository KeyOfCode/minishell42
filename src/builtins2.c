/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/06 16:44:37 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_mini_exit(t_mini *data)
{
	clear_history();
	ft_env_lstclear(data->env_lst);
	// exit(g_status);
	exit(EXIT_SUCCESS);
}

int	echo(t_cmd	*cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (cmd->c_args[1] == NULL)
		ft_putendl_fd("", 1);
	if (cmd->c_args[1] && !ft_strncmp(cmd->c_args[1], "-n", 2))
	{
		flag = 1;
		i = 1;
	}
	while (cmd->c_args[++i])
	{
		ft_putstr_fd(cmd->c_args[i], 2);
		if (cmd->c_args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putendl_fd("", 1);
	return (0);
}

void	set_env(t_mini *data, char *name, char *value)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && !flag)
	{
		if (!ft_strncmp(current->nm, name,
				ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag)
	{
		current->val = value;
		// return (1);
	}
	// return (0);
}

char	*get_env(t_mini *data, char *name)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && !flag)
	{
		if (!ft_strncmp(current->nm, name,
				ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag)
		return (current->val);
	return (0);
}

int	cd(t_mini *data, t_cmd *cmd)
{
	if (!cmd->c_args[1] || !ft_strncmp(cmd->c_args[1], "~", 1))
		cmd->c_args[1] = get_env(data, "HOME");
	else if (!ft_strncmp(cmd->c_args[1], "-", 1))
	{
		if (!get_env(data, "OLDPWD"))
		{
			return (ft_error("bash: cd: OLDPWD not set\n"), 1);
		}
		else
		{
			cmd->c_args[1] = get_env(data, "OLDPWD");
			printf("%s\n", cmd->c_args[1]);
		}
	}
	if (!opendir(cmd->c_args[1]))
	{
		return (ft_error("bash: cd: %s: No such file or directory"), 127);
	}
	set_env(data, "OLDPWD", getcwd(NULL, 0));
	chdir(cmd->c_args[1]);
	set_env(data, "PWD", getcwd(NULL, 0));
	return (0);
}
