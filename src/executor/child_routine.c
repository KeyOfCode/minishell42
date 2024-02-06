/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:30:41 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/03 16:51:21 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Devuelve el número de nodos de una lista de tipo t_child
	Enumera cada nodo de dicha lista
*/

int	get_child_numbers(t_child	*childs)
{
	int		i;

	if (!childs)
		return (0);
	i = 1;
	while (childs != NULL)
	{
		childs->child_num = i;
		childs = childs->next;
		i++;
	}
	return (i - 1);
}

/*
	Función para cambiar los fd en funcion de qué hijo se trata
	Debe tener en cuenta si estamos en:
	el primer hijo, un hijo de enmedio o el hijo final
*/

void	redirect_child_fd(t_child	*child, int number_childs)
{
	if(child && number_childs > 1)
	{
		if (child->child_num == 1) // primer nodo
		{
			// redirigir salida hacia el pipe del siguiente nodo
			dup2(child->next->pipe[WRITE_END], STDOUT_FILENO);
			// cerrar una vez usado     
			close(child->next->pipe[WRITE_END]);
		}
		else if (child->child_num == number_childs) // último nodo
		{
			// leemos del pipe, no de la stdin
			dup2(child->pipe[READ_END], STDIN_FILENO);
			// cerrar extremo ya usado (lectura)
			close(child->pipe[READ_END]);
			// cerrar extremo que no vamos a usar (escritura)
			close(child->pipe[WRITE_END]);
		}
		else // nodo de enmedio: lee de su pipe y escribe en el siguiente
		{
			// leemos del pipe, no de la stdin
			dup2(child->pipe[READ_END], STDIN_FILENO);
			// cerrar el extremo ya duplicado (lectura)
			close(child->pipe[READ_END]);
			// cerrar el extremo de escritura del nodo porque ya no lo vamos a necesitar
			close(child->pipe[WRITE_END]);
			// escribimos en el extremo de escritura del siguient pipe
			dup2(child->next->pipe[WRITE_END], STDOUT_FILENO);
			// cerrar el extremo ya duplicado (escritura)
			close(child->next->pipe[WRITE_END]);
			// no cerramos el de lectura porque lo necesitamos para el siguiente nodo
		}
	}
}

/*
	Función para convertir una lista de tipo t_list en un array de strings
*/

char **list_to_array(t_list *list)
{
    int count;
	int i;
	char **array;
    t_list *temp;

	if (!list)
		return (NULL);
	temp = list;
	count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    array = malloc((count + 1) * sizeof(char *));
    if (!array)
        return (NULL);
    temp = list;
	i = 0;
    while (i < count)
    {
        array[i] = ft_strdup(temp->content);
        temp = temp->next;
		i++;
    }
    array[count] = NULL;
    return (array);
}

/*
	Antes de ejecutar los comandos los fd deben estar redirigidos
	y luego ejecutar los comandos con excesve de forma independiente
	ya que pisaría el proceso padre si no se hace mediante un hijo
*/

void	child_routine(t_child *child, int number_childs)
{
	if (child && number_childs > 0)
	{
		if (number_childs == 1) // si hay un solo hijo
		{
			if (child->infile != STDIN_FILENO)
				dup2(child->infile, STDIN_FILENO);
			if (child->outfile != STDOUT_FILENO)
				dup2(child->outfile, STDOUT_FILENO);
		}
		else if (number_childs > 1) // si hay más de un hijo, redirigir los fd
		{
			redirect_child_fd(child, number_childs);
		}
		// Ejecutar el comando del hijo con execve
		if (child->full_path != NULL && child->cmd_table != NULL)
		{
			char **cmd = list_to_array(child->cmd_table); 
			// execve requiere que los argumentos del comando sean un array de strings
			execve(child->full_path, cmd, child->env);
			// Si llegamos aquí, hubo un error al ejecutar execve
			cmd = free_matrix(cmd);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}
