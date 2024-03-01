/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/01 19:35:15 by darismen         ###   ########.fr       */
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

void	ft_redir(t_mini *data, t_cmd *cmd)
{
	// (void)data;
	if (cmd->fd[READ_END] != data->saved_stdin)
	{
		close(cmd->fd[WRITE_END]);
		dup2(cmd->fd[READ_END], STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	if (cmd->fd[WRITE_END] != data->saved_stdout)
	{
		close(cmd->fd[READ_END]);
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
}

void	builtin(t_mini	*data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", l) || !ft_strncmp(cmd, "PWD", l))
		g_status = pwd();
	else if (!ft_strncmp(cmd, "env", l) || !ft_strncmp(cmd, "ENV", l))
		g_status = env(data);
	else if (!ft_strncmp(cmd, "echo", l) || !ft_strncmp(cmd, "ECHO", l))
		g_status = echo(head);
	else if (!ft_strncmp(cmd, "cd", l))
		g_status = cd(data, head);
	else if (!ft_strncmp(cmd, "export", l))
		g_status = export(data, head);
	else if (!ft_strncmp(cmd, "unset", l))
		g_status = unset(data, head);
	else if (!ft_strncmp(cmd, "exit", l))
		ft_mini_exit(data);
	else
		g_status = ft_executor(data, head);
}

void	ft_re_exe(t_mini *data, t_cmd *cmd);

void	ft_parser(t_mini *data)
{
	t_cmd	*head;

	head = data->cmd_lst;
	if (!head)
		return ;
	while (head)
	{
		ft_putstr_fd(head->c_abs_path, 2);
		ft_putstr_fd("\n", 2);
		ft_redir(data, head);
		builtin(data, head);
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		head = head->next;
	}
	free_cmds(&data->cmd_lst);
}
