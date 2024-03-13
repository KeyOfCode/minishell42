/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/12 17:40:38 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		isbuiltin(t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", l) || !ft_strncmp(cmd, "export", l)
		|| !ft_strncmp(cmd, "unset", l) || !ft_strncmp(cmd, "exit", l)
		|| !ft_strncmp(cmd, "pwd", l) || !ft_strncmp(cmd, "env", l)
		|| !ft_strncmp(cmd, "echo", l))
	{
		return (1);
	}
	return (0);
}

void	ft_builtin(t_mini *data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", l))
		g_exit_code = cd(data, head);
	if (!ft_strncmp(cmd, "export", l) && head->c_args[1])
		g_exit_code = export(data, head);
	if (!ft_strncmp(cmd, "unset", l))
		g_exit_code = unset(data, head);
	if (!ft_strncmp(cmd, "exit", l))
		ft_mini_exit(data);
}

void	ft_printf_fd(int fd, char const *str, ...)
{
	int		i;
	va_list	ap;

	i = 0;
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'c')
				ft_putchar_fd(va_arg(ap, int), fd);
			else if (str[i + 1] == 's')
				ft_putstr_fd(va_arg(ap, char *), fd);
			else if (str[i + 1] == 'i' || str[i + 1] == 'd')
				ft_putnbr_fd(va_arg(ap, int), fd);
			i += 1;
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(ap);
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
		g_exit_code = ft_executor(data, cmd);
		cmd = cmd->next;
	}
	close(data->fd[READ_END]);
	close(data->fd[WRITE_END]);
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	free_cmds(&data->cmd_lst);
}
