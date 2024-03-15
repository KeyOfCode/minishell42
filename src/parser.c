/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/15 11:16:45 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		isbuiltin(t_cmd *head)
{
	char	*cmd;

	cmd = head->c_abs_path;
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "echo", 4))
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
		g_status = cd(data, head);
	if (!ft_strncmp(cmd, "export", 6) && head->c_args[1])
		g_status = export(data, head);
	if (!ft_strncmp(cmd, "unset", 5))
		g_status = unset(data, head);
	if (!ft_strncmp(cmd, "exit", 4))
		ft_mini_exit(data);
}

void	ft_parser(t_mini *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_lst;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (isbuiltin(cmd))
			ft_builtin(data, cmd);
		g_status = ft_executor(data, cmd);
		cmd = cmd->next;
	}
	close(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	free_cmdlst(&data->cmd_lst);
}
