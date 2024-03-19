/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/19 14:48:21 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir(t_cmd *cmd)
{
	if (cmd->fd[READ_END] != -1)
	{
		//close(fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		//close(cmd->fd[READ_END]);
	}
	if (cmd->fd[WRITE_END] != -1)
	{
		//close(fd[READ_END]);
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		//close(cmd->fd[WRITE_END]);
	}
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
	if (cmd->next)
	{
		close(data->fd[READ_END]);
		dup2(data->fd[WRITE_END], STDOUT_FILENO);
		close(data->fd[WRITE_END]);
	}
	ft_redir(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (isbuiltin(cmd))
	{
		child_builtin(cmd->data, cmd);
		exit(g_status);
	}
	if (!get_cmd_path(cmd->data, cmd))
	{
		if (!isdir(cmd->c_abs_path))
			ft_error("minishell: command not found: %s\n", cmd->c_abs_path);
		else
			ft_error("minishell: %s: is a directory\n", cmd->c_abs_path);
	}
	else
		execve(cmd->c_env_path, cmd->c_args, cmd->data->envp);
	exit(127);
}

void	parent_process(int *fd, int pid, int *exit_code)
{
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	waitpid(pid, exit_code, 0);
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
	int		exit_code;

	exit_code = 0;
	update_envp(data);
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
		parent_process(data->fd, pid, &exit_code);
	close(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	close(cmd->fd[READ_END]);
	close(cmd->fd[WRITE_END]);
	return (WEXITSTATUS(exit_code));
}
