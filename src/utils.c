/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/12 17:58:40 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code;

void	ft_error(char *err_msg)
{
	g_exit_code = 1;
	ft_putendl_fd(err_msg, 2);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_print_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		ft_putstr_fd("&", 2);
		ft_putstr_fd(splits[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

void	ft_print_cmds(t_cmd **cmds)
{
	int		i;
	t_cmd 	*cmd;

	cmd = *cmds;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->c_args[i] != NULL)
		{
			ft_putstr_fd("=", 2);
			ft_putstr_fd(cmd->c_args[i++], 2);
			ft_putstr_fd("\n", 2);
		}
		cmd = cmd->next;
	}
}

char	*ft_join_free(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	return (aux);
}

void	handle_sigint(int sig)
{
	// if (data->pid != 0 && data->pid != -1)
	// {
	// 	printf("\n");
	// 	kill(data->pid, SIGKILL);
	// 	g_exit_code = 130;
	// 	data->pid = 0;
	// }
	if (sig == SIGINT)
	{
		rl_redisplay();
		printf("  \n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
		// g_status = 130;
		// rl_redisplay();
		// ft_putstr_fd("\n", STDOUT_FILENO);
		// // ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();

	// if (g_status != 0 && g_status != -1)
	// {
	// 	ft_putstr("\n");
	// 	kill (g_status, SIGKILL);
	// 	g_status = 130;
	// 	g_status = 0;
	// }

