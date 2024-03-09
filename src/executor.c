/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/09 19:12:01 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir(t_cmd *cmd)
{
	if (cmd->fd[READ_END] != -1)
	{
		// close(cmd->fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		// close(cmd->fd[READ_END]);
	}
	if (cmd->fd[WRITE_END] != -1)
	{
		// close(cmd->fd[READ_END]);
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		// close(cmd->fd[WRITE_END]);
	}
	ft_printf_fd(2, "Infile: %d\n", cmd->fd[READ_END]);
	ft_printf_fd(2, "Outfile: %d\n", cmd->fd[WRITE_END]);
}

void	child_process(int *fd, t_cmd *cmd)
{
	if (cmd->next)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
	}
	ft_redir(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_printf_fd(2, "child READ: %d\n", fd[READ_END]);
	ft_printf_fd(2, "child WRITE: %d\n", fd[WRITE_END]);
	if (!ft_builtin(cmd->data, cmd))
	{
		if (!get_cmd_path(cmd->data, cmd))
			ft_error("bash: command not found");
		else
			execve(cmd->c_env_path, cmd->c_args, cmd->data->envp);
	}
	exit (127);
}

/* void	child_process(t_mini *data, t_cmd *cmd)
{
	if (cmd->next)
	{
		close(data->fd[READ_END]);
		dup2(data->fd[WRITE_END], STDOUT_FILENO);
		close(data->fd[WRITE_END]);
	}
	if (cmd->fd[READ_END] != STDIN_FILENO)
	{
		close(fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->c_env_path, cmd->c_args, data->envp);
	exit (127);
} */

	// close(data->fd[READ_END]);
	// dup2(data->fd[WRITE_END], STDOUT_FILENO);
	// dup2(cmd->fd[WRITE_END], data->fd[WRITE_END]);
	// close(data->fd[WRITE_END]);
	// if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	// {
	// 	close(data->fd[READ_END]);
	// 	dup2(data->fd[WRITE_END], cmd->fd[WRITE_END]);
	// 	close(data->fd[WRITE_END]);
	// }

	// close(cmd->next->pipes->fd[WRITE_END]);
// pipe(cmd->pipes->fd);
// 		dup2(cmd->next->pipes->fd[READ_END], cmd->pipes->fd[WRITE_END]);
// 		dup2(cmd->pipes->fd[READ_END], cmd->next->pipes->fd[WRITE_END]);

void	parent_process(int *fd, t_cmd *cmd, int pid, int *exit_code)
{
	(void)cmd;
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	waitpid(pid, exit_code, 0);
}

/* void	parent_process(t_mini *data, t_cmd *cmd, int pid, int *exit_code)
{
	if (cmd->next)
	{
		cmd->fd[READ_END] = dup(fd[READ_END]);
	}
	if (cmd->next)
	{
		close(data->fd[WRITE_END]);
		dup2(data->fd[READ_END], STDIN_FILENO);
		close(data->fd[READ_END]);
	}
	if (cmd->next)
	{
		close(cmd->fd[WRITE_END]);
		cmd->fd[READ_END] = dup(fd[READ_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	if (cmd->fd[READ_END] != STDIN_FILENO)
	{
		close(fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	waitpid(pid, exit_code, 0);
} */

	// dup2(cmd->fd[READ_END], data->fd[READ_END]);
	// if (cmd->fd[READ_END] != STDIN_FILENO)
	// 	dup2(data->fd[READ_END], cmd->fd[READ_END]);

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
		if (pipe(data->fd) == -1)
			return (ft_error("Pipe Error"), 1);
	ft_printf_fd(2, "data READ: %d\n", data->fd[READ_END]);
	ft_printf_fd(2, "data WRITE: %d\n", data->fd[WRITE_END]);
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error"), 1);
	else if (pid == 0)
		child_process(data->fd, cmd);
	else
		parent_process(data->fd, cmd, pid, &exit_code);
	ft_putstr_fd("\nft_Executor finish\n", 2);
	close(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	close(cmd->fd[READ_END]);
	close(cmd->fd[WRITE_END]);
	// data->fd[WRITE_END] = dup(data->saved_stdin);
	// data->fd[READ_END] = dup(data->saved_stdout);
	return (WEXITSTATUS(exit_code));
}

	// if (cmd->next)
	// 	if (pipe(cmd->fd) == -1)
	// 		return (ft_error("Pipe Error"), 1);

/**
 * 
 * @param data 
 * @param cmd 
 * @return int 
 */
/* int	ft_executor(t_mini *data, t_cmd *cmd)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	update_envp(data);
	if (cmd->next)
		if (pipe(data->fd) == -1)
			return (ft_error("Pipe Error"), 1);
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error"), 1);
	else if (pid == 0)
	{
		if (!get_cmd_path(data, cmd))
			return (ft_error("bash: command not found"), 127);
		child_process(data, cmd);
	}
	else
		parent_process(data, cmd, pid, &exit_code);
	data->fd[WRITE_END] = dup(data->saved_stdin);
	return (WEXITSTATUS(exit_code));
} */

	// ft_free_matrix(data->envp);

/* 
printf("Check: get_env_path. env_path: %s\n", cmd->c_env_path);
printf("Check: update_envp\n");
update_envp(data);
execve(cmd->c_env_path, cmd->c_args, data->envp);
free(data->envp);
 */
