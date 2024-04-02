/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/04/02 15:01:03 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir(t_mini *data, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		close(data->fd[READ_END]);
		dup2(data->fd[WRITE_END], STDOUT_FILENO);
		close(data->fd[WRITE_END]);
	}
	if (cmd->fd[READ_END] != -1)
	{
		dup2(cmd->fd[READ_END], STDIN_FILENO);
	}
	if (cmd->fd[WRITE_END] != -1)
	{
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
	}
	close(cmd->fd[READ_END]);
	close(cmd->fd[WRITE_END]);
}

void	child_builtin(t_mini *data, t_cmd *head)
{
	char	*cmd;

	cmd = head->c_abs_path;
	if (!ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "PWD", 3))
	{
		g_status = pwd();
	}
	if (!ft_strncmp(cmd, "env", 3) || !ft_strncmp(cmd, "ENV", 3))
	{
		g_status = env(data);
	}
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "ECHO", 4))
	{
		g_status = echo(head);
	}
	if (!ft_strncmp(cmd, "export", 6) && !head->c_args[1])
	{
		g_status = export(data, head);
	}
}

void	child_process(t_mini *data, t_cmd *cmd)
{
	ft_redir(data, cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_child_builtin(cmd))
	{
		child_builtin(cmd->data, cmd);
		exit(g_status);
	}
	if (!get_cmd_path(cmd->data, cmd))
	{
		if (!isdir(cmd->c_abs_path))
		{
			ft_error("minishell: %s: command not found\n", cmd->c_abs_path);
			exit(127);
		}
		else
			ft_error("minishell: %s: is a directory\n", cmd->c_abs_path);
	}
	else
		execve(cmd->c_env_path, cmd->c_args, cmd->data->envp);
	exit(126);
}

void	parent_process(t_mini *data, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		dup2(data->fd[READ_END], STDIN_FILENO);
	}
	close(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	close(cmd->fd[READ_END]);
	close(cmd->fd[WRITE_END]);
}

/**
 * 
 * @param data 
 * @param cmd 
 * @return int 
 */
int	ft_executor(t_mini *data, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(data->fd) == -1)
			return (ft_error("Pipe Error\n", NULL), 1);
	}
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error\n", NULL), 1);
	if (pid == 0)
	{
		child_process(data, cmd);
	}
	else
		parent_process(data, cmd);
	return (0);
}

// /Users/darismen/.brew/bin:/bin/:/usr/local/bin:/usr/bin