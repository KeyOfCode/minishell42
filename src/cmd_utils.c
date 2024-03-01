/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:16:18 by disantam          #+#    #+#             */
/*   Updated: 2024/02/26 19:03:32 by darismen         ###   ########.fr       */
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
	char	count_print;

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
	count_print = '0' + count;
	write(2, &count_print, 1);
	write(2, "-\n", 2);
	return (count);
}

void	redir_error(char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	write(2, token, 1);
	write(2, "`\n", 2);
	g_status = 1;
}

void	free_cmds(t_cmd **cmd_lst)
{
	int		i;
	t_cmd	*head;

	head = *cmd_lst;
	while (*cmd_lst != NULL)
	{
		head = *cmd_lst;
		i =-1;
		while (head->c_args[++i] != NULL)
		{
			free(head->c_args[i]);
		}
		free(head->c_args);
		*cmd_lst = head->next;
		free(head);
	}
}
