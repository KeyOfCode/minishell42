/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipe_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:02:26 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/01 16:35:06 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

*/

void	init_node(t_mini *node)
{
	if (node != NULL)
	{
		node->full_cmd = NULL;
		node->full_path = NULL;
		node->infile = STDIN_FILENO;
		node->outfile = STDOUT_FILENO;
	}
}

void	create_pipe_node(t_list **cmds)
{
	t_mini  *new_node;
	t_list  *add_cmd;

	new_node = NULL;
	add_cmd = NULL;
	//crear un nuevo nodo mini
	new_node = (t_mini *)malloc(sizeof(t_mini));
	init_node(new_node);
	// crear nuevo nodo lista
	add_cmd = (t_list *)malloc(sizeof(t_list));
	add_cmd->content = new_node;
	add_cmd->next = NULL;
	// añadir a la lista de comandos
	ft_lstadd_back(cmds, add_cmd);
}

int	main(int argc, char **argv)
{
	(void)argv;
	t_list	**cmds;

	cmds = NULL;
	if (argc == 2)
	{
		pipe_node(cmds);
		
	}
	return (0);
}