/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:02:57 by darismen          #+#    #+#             */
/*   Updated: 2022/10/17 14:07:34 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;
	t_list	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	last_elem = current;
	last_elem->next = new;
}

/* 
Parámetros
	lst: el puntero al primer nodo de una lista.
	new: el puntero a un nodo que añadir a la lista.
Descripción 
	Añade el nodo ’new’ al final de la lista ’lst’. 
*/