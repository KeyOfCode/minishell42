/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:56:26 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/18 13:08:50 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void    init_node(t_mini *node)
{
	if (node != NULL)
	{
		node->full_cmd = NULL;
		node->full_path = NULL;
		node->infile = STDIN_FILENO;
		node->outfile = STDOUT_FILENO;
	}
}

void	check_token(char *str, t_list **cmds)
{
	t_mini  *new_node;
	t_list  *add_cmd;

	new_node = NULL;
	add_cmd = NULL;
	if (str == NULL || *str = '\0')
		return ;
	if (*str == '|')
	{
		//crear un nuevo nodo mini
		new_node = (t_mini *)malloc(sizeof(t_mini));
		init_node(new_node);
		// crear nuevo nodo lista
		add_cmd = (t_list *)malloc(sizeof(t_list));
		add_cmd->content = new_node;
		add_cmd->next = NULL
		// añadir a la lista de comandos
		ft_lstadd_back(cmds, add_cmd);
	}
	else if (*str == '<' || *str == '<<' || *str == '>' || *str == '>>')
	{
		// ajustar fd infile y outfile
		// char **tokens, el nodo actual (último)
	}
	else 
		// agregar a lista de argumentos full_cmd
}


void	parser(char **tokens, t_list *cmds)
{
	if (tokens != NULL)
	{
		while (tokens != NULL)
		{
			check_token(*tokens, &cmds);
			tokens++;
		}
	}
}