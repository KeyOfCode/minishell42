/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/08 14:51:03 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtin(t_mini *data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", l))
		g_status.exit_code = cd(data, head);
	else if (!ft_strncmp(cmd, "export", l) && head->c_args[1])
		g_status.exit_code = export(data, head);
	else if (!ft_strncmp(cmd, "unset", l))
		g_status.exit_code = unset(data, head);
	else if (!ft_strncmp(cmd, "exit", l))
		ft_mini_exit(data);
	else
		g_status.exit_code = ft_executor(data, head);	
	return (0);
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

