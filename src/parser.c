/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/23 15:52:36 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_parent_builtin(t_cmd *head)
{
	char	*cmd;

	cmd = head->c_abs_path;
	if (!ft_strncmp(cmd, "exit", 4)
		|| !ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "unset", 5)
		|| (!ft_strncmp(cmd, "export", 6) && head->c_args[1]))
	{
		return (1);
	}
	return (0);
}

int	is_child_builtin(t_cmd *head)
{
	char	*cmd;

	cmd = head->c_abs_path;
	if (!ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "env", 3)
		|| (!ft_strncmp(cmd, "export", 6) && !head->c_args[1]))
	{
		return (1);
	}
	return (0);
}

void	ft_builtin(t_mini *data, t_cmd *head)
{
	char	*cmd;

	cmd = head->c_abs_path;
	if (!ft_strncmp(cmd, "cd", 2))
	{
		g_status = cd(data, head);
	}
	if (!ft_strncmp(cmd, "export", 6) && head->c_args[1])
	{
		g_status = export(data, head);
	}
	if (!ft_strncmp(cmd, "unset", 5))
	{
		g_status = unset(data, head);
	}
	if (!ft_strncmp(cmd, "exit", 4))
	{
		ft_mini_exit(data, head);
	}
}

int	ft_parser(t_mini *data)
{
	t_cmd	*cmd;
	int		i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	cmd = data->cmd_lst;
	while (cmd)
	{
		update_envp(data);
		if (is_parent_builtin(cmd))
			ft_builtin(data, cmd);
		else
			ft_executor(data, cmd);
		cmd = cmd->next;
		i++;
	}
	dup2(data->saved_stdin, STDIN_FILENO);
	// atexit(leaks);
	while (i-- > 0)
		waitpid(-1, &exit_code, 0);
	dup2(data->saved_stdout, STDOUT_FILENO);
	free_cmdlst(&data->cmd_lst);
	ft_free_matrix(data->full_cmd);
	return (ft_free_matrix(data->full_path), WEXITSTATUS(exit_code));
}

	// if (!cmd)
	// 	return ;