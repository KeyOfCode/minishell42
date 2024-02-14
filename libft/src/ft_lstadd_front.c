/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:37:39 by darismen          #+#    #+#             */
/*   Updated: 2022/10/07 16:56:22 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* Parámetros 
	lst: la dirección de un puntero al primer nodo de
		una lista.
	new: un puntero al nodo que añadir al principio de
		la lista.
Valor devuelto 
	Nada
Descripción 
	Añade el nodo ’new’ al principio de la lista ’lst’. */