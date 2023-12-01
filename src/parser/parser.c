/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:56:26 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/01 16:43:20 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_token(char *str, t_list **cmds)
{
	if (str == NULL || *str = '\0')
		return ;
	if (*str == '|')
	{
		create_pipe_node(cmds);
	}
	else if (*str == '>')
	{
		//redirecciona salida(stdout).
	}
	else if (*str == '>>')
	{
		//agrega el contenido a la salida en vez de sobreescribirlo
	}
	else if (*str == '<')
	{
		//redirecciona la entrada (stdin).
	}
	else if (*str == '<<')
	{
		//hereDoc
	}
	else
	{
		// agregar a lista de argumentos full_cmd
	}
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