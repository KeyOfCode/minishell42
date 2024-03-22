/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:16:18 by disantam          #+#    #+#             */
/*   Updated: 2024/03/21 14:26:24 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isredir(char *arg)
{
	if (!ft_strncmp(arg, "<", 1) || !ft_strncmp(arg, ">", 1)
		|| !ft_strncmp(arg, "<<", 2) || !ft_strncmp(arg, ">>", 2))
	{
		return (1);
	}
	return (0);
}

int	count_cmdargs(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (args[i] && ft_strncmp(args[i], "|", 1))
	{
		if (!isredir(args[i]))
		{
			count++;
		}
		else if (args[i + 1])
		{
			i++;
		}
		i++;
	}
	return (count);
}

void	free_fullcmd(char **args)
{
	int	i;

	i = -1;
	while (args[++i] != NULL)
	{
		free(args[i]);
	}
	free(args);
}

void	free_cmdlst(t_cmd **cmd_lst)
{
	t_cmd	*head;

	head = *cmd_lst;
	while (*cmd_lst != NULL)
	{
		head = *cmd_lst;
		if (head->c_env_path != NULL)
		{
			free(head->c_env_path);
		}
		free(head->c_args);
		*cmd_lst = head->next;
		free(head);
	}
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix != NULL)
	{
		while (matrix[++i] != NULL)
		{
			free(matrix[i]);
		}
		free(matrix);
	}
}
