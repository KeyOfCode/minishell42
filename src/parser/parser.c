/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:56:26 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/08 18:49:00 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_cmd_table(char *str, t_child *childs)
{
	t_child	*last_child;
	char	*dup_str;
	t_list 	*new_cmd;

	if (str && childs)
	{
		dup_str = ft_strdup(str);
		if (!dup_str)
			return ;
		new_cmd = ft_lstnew(dup_str);
		last_child = get_last_child(childs);
		ft_lstadd_back(&last_child->cmd_table, new_cmd);
	}
}

void	check_token(char *str, t_child *childs,char **tokens)
{
	if (str == NULL || *str = '\0')
		return ;
	if (ft_strncmp(str, "|", 1) && ft_strlen(str) == 1)
	{
		new_child_node(childs);
	}
	else if (ft_strncmp(str, ">", 1) && ft_strlen(str) == 1)
		output_redir(childs, tokens);
	else if (ft_strncmp(str, ">>", 2) && ft_strlen(str) == 2)
		output_redir_append(childs, tokens);
	else if (ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		input_redir(childs, tokens);
	else if (ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
	{
		//	hereDoc
	}
	else
	{
		//	agregar a lista de argumentos full_cmd:
	}
}

void	parser(char **tokens, t_child *childs)
{
	if (tokens != NULL)
	{
		new_child_node(childs);
		while (tokens != NULL)
		{
			check_token(*tokens, childs, tokens);
			tokens++;
		}
	}
}