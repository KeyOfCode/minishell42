/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_child_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:02:26 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/03 16:35:30 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

Inicializamos child_num, heredoc, pid y status a 0. 
El array del pipe se inicializa a -1, que es un valor que normalmente no se obtiene al crear un pipe, por lo que es un buen valor para indicar que el pipe aún no se ha creado. 
Los punteros se inicializan a NULL, que es un valor razonable para un puntero que aún no apunta a nada.

*/
void	init_child_node(t_child *child)
{
    if (child != NULL)
    {
        child->cmd_table = NULL;
        child->full_path = NULL;
        child->env = NULL;
        child->child_num = 0;
        child->heredoc = 0;
        child->pipe[0] = -1;
        child->pipe[1] = -1;
        child->pid = -1;
        child->status = 0;
        child->next = NULL;
    }
}

void add_child_back(t_child **head, t_child *to_add)
{
	t_child *last;

	last = NULL;
	if (*head == NULL)
		*head = to_add;
	else 
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = to_add;
	}
}

void	new_child_node(t_child *childs)
{
	t_child	*new;

	new = (t_child *)malloc(sizeof(t_child));
	if (!new)
		return ;
	init_child_node(new);
	add_child_back(&childs, new);
	return (new);
}

// Función para obtener el último nodo de la lista enlazada de t_child
t_child	*get_last_child(t_child *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}
