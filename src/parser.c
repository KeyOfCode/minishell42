/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/01/24 19:58:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* int	is_builtin(char *cmd)
{
	int	l;

	l = ft_strlen (cmd);
	if (!ft_strncmp(cmd, "pwd", l))
		return (1);
} */

/* Para export, considerar separa el prompt utilizando "=" como caracter 
especial */
void	builtin(t_mini	*data, t_cmd *head)
{
	char	*cmd;
	int		l;

	cmd = head->c_abs_path;
	l = ft_strlen (cmd);
	if (!ft_strncmp(cmd, "pwd", l))
		pwd();
	else if (!ft_strncmp(cmd, "env", l))
		env(data);
	else if (!ft_strncmp(cmd, "export", l) && !head->c_args[1])
		empty_export(data);
	else if (!ft_strncmp(cmd, "export", l))
		export(data, head);
}

void	ft_parser(t_mini *data)
{
	t_cmd	*head;

	head = *data->cmd_lst;
	if (!head)
		return ;
	while (head)
	{
		printf("%s\n", head->c_abs_path);
		builtin(data, head);
		head = head->next;
	}
}
