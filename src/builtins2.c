/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/04/01 21:47:52 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(t_cmd	*cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (cmd->c_args[1] == NULL)
	{
		ft_putendl_fd("", 1);
		return (0);
	}
	if (cmd->c_args[1] && !ft_strncmp(cmd->c_args[1], "-n", 2))
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
		ft_putendl_fd("", 1);
	return (0);
}

char	*ft_path_cd(t_mini *data, t_cmd *cmd)
{
	char	*path;

	path = cmd->c_args[1];
	if (!cmd->c_args[1] || !ft_strncmp(path, "~", 1))
		path = get_env(data, "HOME");
	else if (!ft_strncmp(path, "-", 1))
	{
		if (!get_env(data, "OLDPWD"))
			return (ft_error("minishell: cd: OLDPWD not set\n", NULL), NULL);
		else
			path = get_env(data, "OLDPWD");
		ft_printf_fd(1, "%s\n", path);
	}
	return (path);
}

int	access_dir(char *path)
{
	DIR		*current;

	current = opendir(path);
	if (!current)
		return (ft_error("minishell: cd: %s: No such \
file or directory\n", path), 1);
	closedir(current);
	if (access(path, R_OK | W_OK) == -1)
		return (ft_error("minishell: cd: %s: Permission denied\n", path), 1);
	return (0);
}

int	cd(t_mini *data, t_cmd *cmd)
{
	char	*path;

	path = ft_path_cd(data, cmd);
	if (!path)
		return (1);
	if (access_dir(path) != 0)
		return (1);
	set_env(data, "OLDPWD", get_env(data, "PWD"));
	chdir(path);
	path = getcwd(NULL, 0);
	set_env(data, "PWD", path);
	if (path)
		free(path);
	return (0);
}
