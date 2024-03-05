/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/05 16:55:33 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exe(t_mini *data, t_cmd *cmd)
{
	execve(cmd->c_env_path, cmd->c_args, data->envp);
	exit (127);
}

void	child_process(t_mini *data, t_cmd *cmd, int *fd)
{
	if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	{|
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
	if (cmd->fd[READ_END] != STDIN_FILENO)
	{
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	if (cmd->next && cmd->fd[WRITE_END] == STDOUT_FILENO)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
	}
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_exe(data, cmd);
}

// close(cmd->next->pipes->fd[WRITE_END]);
// pipe(cmd->pipes->fd);
// dup2(cmd->next->pipes->fd[READ_END], cmd->pipes->fd[WRITE_END]);
// dup2(cmd->pipes->fd[READ_END], cmd->next->pipes->fd[WRITE_END]);

void	parent_process(t_cmd *cmd, int *fd, int pid, int *exit_code)
{
	if (cmd->next && cmd->fd[READ_END] == STDIN_FILENO)
	{
		cmd->fd[READ_END] = fd[READ_END];
	}
	close(fd[WRITE_END]);
	close(fd[READ_END]);
	waitpid(pid, exit_code, 0);
}

/**
 * ! In it's current state, unknown commands have leaks, fix.
 * 
 * @param data 
 * @param cmd 
 * @return int 
 */
int	ft_executor(t_mini *data, t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];
	int		exit_code;

	exit_code = 0;
	update_envp(data);
	// if (!get_cmd_path(data, cmd))
	// 	ft_error("bash: command not found");
	if (pipe(fd) == -1)
		return (ft_error("Pipe Error"), 1);
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error"), 1);
	else if (pid == 0)
	{
		if (!get_cmd_path(data, cmd))
			return (ft_error("bash: command not found"), 127);
		child_process(data, cmd, fd);
	}
	else
		parent_process(cmd, fd, pid, &exit_code);
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	// data->fd[WRITE_END] = dup(data->saved_stdin);
	return (WEXITSTATUS(exit_code));
}

	// ft_free_matrix(data->envp);
// execve(cmd->c_env_path, cmd->c_args, data->envp);
// 		free(data->envp);
// 		exit (127);

/* 
printf("Check: get_env_path. env_path: %s\n", cmd->c_env_path);
printf("Check: update_envp\n");
update_envp(data);
execve(cmd->c_env_path, cmd->c_args, data->envp);
free(data->envp);
 */
