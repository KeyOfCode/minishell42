/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:55:24 by darismen          #+#    #+#             */
/*   Updated: 2022/10/20 14:42:18 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* Parámetros
	lst: un puntero al primer nodo.
	f: un puntero a la función que utilizará cada nodo.
Valor devuelto
	Nada
Funciones autorizadas
	Ninguna
Descripción
	Itera la lista ’lst’ y aplica la función ’f’ en el
contenido de cada nodo. */