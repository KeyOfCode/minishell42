/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/02/22 12:49:36 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_error(char *err_msg)
{
	g_status = 1;
	ft_putendl_fd(err_msg, 2);
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

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		rl_redisplay();
		ft_putstr_fd("  \n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	ft_ctrl_d(t_mini *data)
// {
// 	if (!data->prompt)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 		ft_putstr_fd("exit\n", STDOUT_FILENO);
// 		clear_history();
// 		ft_env_lstclear(data->env_lst);
// 		exit(g_status);
// 	}
// }
