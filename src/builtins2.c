/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/20 12:02:03 by disantam         ###   ########.fr       */
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
		current->val = value;
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
	return (NULL);
}

int	cd(t_mini *data, t_cmd *cmd)
{
	char	*path;

	path = cmd->c_args[1];
	if (!path || !ft_strncmp(path, "~", 1))
	{
		path = get_env(data, "HOME");
	}
	else if (!ft_strncmp(path, "-", 1))
	{
		if (!get_env(data, "OLDPWD"))
			return (ft_error("minishell: cd: OLDPWD not set\n", NULL), 1);
		else
		{
			path = get_env(data, "OLDPWD");
		}
	}
	if (!opendir(path))
	{
		return (ft_error("minishell: cd: %s: No such \
file or directory\n", path), 127);
	}
	set_env(data, "OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_env(data, "PWD", getcwd(NULL, 0));
	return (0);
}
