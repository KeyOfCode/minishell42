/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/01/28 20:04:46 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* int	is_builtin(char *cmd)
{
	int	l;

	l = ft_strlen (cmd);
	if (!ft_strncmp(cmd, "pwd", l))
		return (1);
} */

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

/**
 * TODO Handle error: No directory exists. Print error correctly.
 * 
 */
void	cd(t_mini *data, t_cmd *cmd)
{
	if (!cmd->c_args[1] || !ft_strncmp(cmd->c_args[1], "~", 1))
		cmd->c_args[1] = get_env(data, "HOME");
	else if (!ft_strncmp(cmd->c_args[1], "-", 1))
	{
		if (!get_env(data, "OLDPWD"))
		{
			printf("bash: cd: OLDPWD not set\n");
			return ;
		}
		else
		{
			cmd->c_args[1] = get_env(data, "OLDPWD");
			printf("%s\n", cmd->c_args[1]);
		}
	}
	set_env(data, "OLDPWD", getcwd(NULL, 0));
	chdir(cmd->c_args[1]);
	set_env(data, "PWD", getcwd(NULL, 0));
}

void	builtin(t_mini	*data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen (cmd);
	if (!ft_strncmp(cmd, "pwd", l))
		pwd();
	else if (!ft_strncmp(cmd, "env", l))
		env(data);
	else if (!ft_strncmp(cmd, "export", l))
		export(data, head);
	else if (!ft_strncmp(cmd, "unset", l))
		unset(data, head);
	else if (!ft_strncmp(cmd, "cd", l))
		cd(data, head);
	// else if (!ft_strncmp(cmd, "exit", l))
	// 	ft_mini_exit(data, head);
}

void	ft_parser(t_mini *data)
{
	t_cmd	*head;

	head = *data->cmd_lst;
	if (!head)
		return ;
	while (head)
	{
		printf("%s\n", head->c_abs_path);
		builtin(data, head);
		head = head->next;
	}
}
