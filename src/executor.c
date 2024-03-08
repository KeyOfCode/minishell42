/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/08 15:09:06 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir(int *fd, t_cmd *cmd)
{
	if (cmd->fd[READ_END] != STDIN_FILENO)
	{
		close(fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	{
		close(fd[READ_END]);
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
}

int	child_builtin(t_mini *data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", l) || !ft_strncmp(cmd, "PWD", l))
		g_status.exit_code = pwd();
	else if (!ft_strncmp(cmd, "env", l) || !ft_strncmp(cmd, "ENV", l))
		g_status.exit_code = env(data);
	else if (!ft_strncmp(cmd, "echo", l) || !ft_strncmp(cmd, "ECHO", l))
		g_status.exit_code = echo(head);
	else if (!ft_strncmp(cmd, "export", l) && !head->c_args[1])
		g_status.exit_code = export(data, head); 
	else
		return (0);
	return (1);
}

void	child_process(int *fd, t_cmd *cmd)
{
	close(fd[READ_END]);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	ft_redir(fd, cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!child_builtin(cmd->data, cmd))
	{
		if (!get_cmd_path(cmd->data, cmd))
			ft_error("bash: command not found");
		else
			execve(cmd->c_env_path, cmd->c_args, cmd->data->envp);
	}
	exit(127);
}

void	parent_process(int *fd, t_cmd *cmd, int pid, int *exit_code)
{
	(void)cmd;
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
	int		fd[2];
	int		exit_code;

	exit_code = 0;
	update_envp(data);
	if (pipe(fd) == -1)
		return (ft_error("Pipe Error"), 1);
	pid = fork();
	if (pid != 0)
		g_status.pid = pid;
	if (pid < 0)
		return (ft_error("Fork Error"), 1);
	else if (pid == 0)
		child_process(fd, cmd);
	else
		parent_process(fd, cmd, pid, &exit_code);
	data->fd[WRITE_END] = dup(data->saved_stdin);
	return (WEXITSTATUS(exit_code));
}
