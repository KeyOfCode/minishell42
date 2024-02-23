/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/02/23 12:15:29 by disantam         ###   ########.fr       */
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

void	builtin(t_mini	*data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", l))
		g_status = pwd();
	else if (!ft_strncmp(cmd, "env", l))
		g_status = env(data);
	else if (!ft_strncmp(cmd, "export", l))
		g_status = export(data, head);
	else if (!ft_strncmp(cmd, "unset", l))
		g_status = unset(data, head);
	else if (!ft_strncmp(cmd, "cd", l))
		g_status = cd(data, head);
	else if (!ft_strncmp(cmd, "echo", l))
		g_status = echo(head);
	else if (!ft_strncmp(cmd, "exit", l))
		ft_mini_exit(data);
	else
		ft_executor(data, head);
}

void	ft_parser(t_mini *data)
{
	t_cmd	*head;

	head = *data->cmd_lst;
	if (!head)
		return ;
	while (head)
	{
		ft_putstr_fd(head->c_abs_path, 2);
		ft_putstr_fd("\n", 2);
		builtin(data, head);
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		head = head->next;
	}
}
