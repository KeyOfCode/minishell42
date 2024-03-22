/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:34:30 by disantam          #+#    #+#             */
/*   Updated: 2024/03/22 12:05:48 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_code(char *arg)
{
	int				i;
	unsigned int	code;

	i = -1;
	while (arg[++i])
	{
		if (ft_isalpha(arg[i]))
		{
			ft_error("minishell: %s: numeric argument required\n",
				arg);
			return (255);
		}
	}
	code = (unsigned int)ft_atoi(arg);
	if (code > 255)
		code = code % 256;
	return (code);
}

void	ft_mini_exit(t_mini *data, t_cmd *cmd)
{
	int	c;

	if (cmd)
		c = count_cmdargs(cmd->c_args);
	if (cmd != NULL && c > 2)
	{
		ft_error("minishell: %s: too many arguments\n", cmd->c_abs_path);
		return ;
	}
	if (cmd && cmd->c_args[1])
		g_status = get_code(cmd->c_args[1]);
	clear_history();
	ft_free_matrix(data->envp);
	ft_env_lstclear(data->env_lst);
	exit(g_status);
}
