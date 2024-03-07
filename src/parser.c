/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/07 15:39:54 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtin(t_mini	*data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	//if (!ft_strncmp(cmd, "pwd", l) || !ft_strncmp(cmd, "PWD", l))
	//	g_status = pwd();
	//else if (!ft_strncmp(cmd, "env", l) || !ft_strncmp(cmd, "ENV", l))
	//	g_status = env(data);
	//else if (!ft_strncmp(cmd, "echo", l) || !ft_strncmp(cmd, "ECHO", l))
	//	g_status = echo(head);
	if (!ft_strncmp(cmd, "cd", l))
		g_status = cd(data, head);
	else if (!ft_strncmp(cmd, "export", l) && head->c_args[1])
		g_status = export(data, head);
	else if (!ft_strncmp(cmd, "unset", l))
		g_status = unset(data, head);
	else if (!ft_strncmp(cmd, "exit", l))
		ft_mini_exit(data);
	else
		g_status = ft_executor(data, head);	
	return (1);
}

void	ft_parser(t_mini *data)
{
	t_cmd	*head;

	head = data->cmd_lst;
	if (!head)
		return ;
	while (head)
	{
		ft_builtin(data, head);
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		head = head->next;
	}
	free_cmds(&data->cmd_lst);
}

