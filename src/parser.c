/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/08 16:53:03 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtin(t_mini	*data, t_cmd *head)
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
		return (0);
	return (1);
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
		g_status = ft_executor(data, cmd);
		// ft_printf_fd(2, "Infile: %d\n", cmd->fd[READ_END]);
		// ft_printf_fd(2, "Outfile: %d\n", cmd->fd[WRITE_END]);
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		ft_putstr_fd("", 0);
		cmd = cmd->next;
	}
	// dup2(data->saved_stdin, STDIN_FILENO);
	// dup2(data->saved_stdout, STDOUT_FILENO);
	ft_printf_fd(2, "saved_stdin: %d\n", data->saved_stdin);
	ft_printf_fd(2, "saved_stdout: %d\n", data->saved_stdout);
	free_cmds(&data->cmd_lst);
}

		// ft_putstr_fd("Infile: ", 2);
		// ft_putnbr_fd(cmd->fd[READ_END], 2);
		// ft_putstr_fd("\n: ", 2);
		// ft_putstr_fd("Outfile: ", 2);
		// ft_putnbr_fd(cmd->fd[WRITE_END], 2);
		// ft_putstr_fd("\n: ", 2);