/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:18:06 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/03 16:24:02 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*	
	Aquí todos los fd de los pipes deben estar abiertos
	porque los hijos heredan los fd del proceso padre
*/

void	execute(t_child *childs)
{
	int		number_childs;
	t_child	*begin_list;

	if (!childs)
		return ;
	begin_list = childs;
	number_childs = get_child_numbers(begin_list);
	// Crear los pipes, excepto el en primero nodo
	if (childs != NULL)
        childs = childs->next; // Mover al segundo nodo
	while(childs != NULL)
	{
		if (pipe(childs->pipe) == -1)
		{
			// error: pipe no se ha podido crear
		}
		childs = childs->next;
	}
	// Crear todos los procesos hijos
	childs = begin_list;
	while(childs != NULL)
	{
		childs->pid = fork();
		if (childs->pid == -1)
		{
			// error: fork no se ha podido crear
		}
		else if (childs->pid == 0)
		{ 
			// rutina hijo
			child_routine(childs, number_childs);
			exit (0); // exit del hijo después de ejecutar
		}
		childs = childs->next;
	}
	childs = begin_list;
	// Esperar a que todos los hijos acaben
	while(childs != NULL)
	{
		waitpid(childs->pid, &childs->status, 0);
		childs = childs->next;
	}
	// Cerrar todos los descriptores de archivo
	childs = begin_list;
	while(childs != NULL)
	{
		if (childs->infile != -1)
		{
			close(childs->infile);
			childs->infile = -1;
		}
		if (childs->outfile != -1)
		{
			close(childs->outfile);
			childs->outfile = -1;
		}
		childs = childs->next;
	}
}