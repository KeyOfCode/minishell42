/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:34:30 by disantam          #+#    #+#             */
/*   Updated: 2024/03/20 13:03:06 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_code(t_cmd *cmd)
{
	int				i;
	unsigned int 	code;

	i = -1;
	while (cmd->c_args[1][++i])
	{
		if (ft_isalpha(cmd->c_args[1][i]))
		{
			ft_error("minishell: %s: numeric argument required\n", 
			cmd->c_args[1]);
			return (255);
		}
	}
	code = ft_atoi(cmd->c_args[1]);
	if (code > 255)
		code = code % 256;
	return (code);
}

void	ft_mini_exit(t_mini *data, t_cmd *cmd)
{
	if (cmd != NULL && cmd->c_count > 2)
	{
		ft_error("minishell: %s: too many arguments\n", cmd->c_abs_path);
		return ;
	}
	if (cmd != NULL && cmd->c_args[1] != NULL)
		g_status = get_code(cmd);
	clear_history();
	ft_free_matrix(data->envp);
	ft_env_lstclear(data->env_lst);
	exit(g_status);
}
