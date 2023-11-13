/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:12:27 by darismen          #+#    #+#             */
/*   Updated: 2022/10/17 14:30:40 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*priv_lstnew(void *content)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!(newlist))
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void	priv_map_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	priv_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		current = *lst;
		priv_map_lstdelone(*lst, del);
		*lst = current->next;
	}
	*lst = NULL;
}

void	priv_lstadd_back(t_list **lst, t_list *new)
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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*newlist;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		newnode = priv_lstnew(f(lst->content));
		if (!newnode)
		{
			priv_lstclear(&newlist, del);
			return (NULL);
		}
		priv_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

/* Parámetros 
	lst: un puntero a un nodo.
	f: la dirección de un puntero a una función usada
		en la iteración de cada elemento de la lista.
	del: un puntero a función utilizado para eliminar
		el contenido de un nodo, si es necesario.
Valor devuelto 
	La nueva lista.
	NULL si falla la reserva de memoria.
Funciones autorizadas
	malloc, free
Descripción 
	Itera la lista ’lst’ y aplica la función ’f’ al
	contenido de cada nodo. Crea una lista resultante
	de la aplicación correcta y sucesiva de la función
	’f’ sobre cada nodo. La función ’del’ se utiliza
	para eliminar el contenido de un nodo, si hace
	falta. */

/* ***************************************************************** */
/* 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void	ft_print_result(t_list *elem)
{
	int		len;

	len = 0;
	while (((char *)elem->content)[len])
		len++;
	write(1, ((char *)elem->content), len);
	write(1, "\n", 1);
}

t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
		elem->content = content;
	elem->next = NULL;
	return (elem);
}

void	*ft_map(void *ct)
{
	int i;
	void	*c;
	char	*pouet;

	c = ct;
	i = -1;
	pouet = (char *)c;
	while (pouet[++i])
		if (pouet[i] == 'o')
			pouet[i] = 'a';
	return (c);
}

void    ft_del(void *content)
{
	free(content);
}

int main(int argc, const char *argv[])
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	t_list		*list;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);

	if (argc == 1 || !elem || !elem2 || !elem3 || !elem4)
		return (0);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	if (atoi(argv[1]) == 1)
	{
		if (!(list = ft_lstmap(elem, &ft_map, &ft_del)))
			return (0);
		if (list == elem)
			write(1, "A new list is not returned\n", 27);
		int i;
		i = 0;
		ft_print_result(list);
		while (list->next)
		{
			list = list->next;
			ft_print_result(list);
			i++;
		}
	}
	return (0);
}


 */