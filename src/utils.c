/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/02/05 16:41:34 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_error(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_SUCCESS);
}

void	ft_print_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		printf("&%s--\n", splits[i]);
		i++;
	}
}

void	ft_ctrl_d(t_mini *data)
{
	if (!data->prompt)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		clear_history();
		ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS);
	}
}

void	ft_free_matrix(char **newarry)
{
	int	i;

	i = 0;
	if (!newarry)
		return ;
	while (newarry[i])
	{
		free(newarry[i]);
		i++;
	}
	free(newarry);
}
