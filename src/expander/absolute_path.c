/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:13:56 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/01 16:48:03 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*remove_last_node(t_list **list)
{
	t_list	*last;
	t_list	*new_last;

	if (*list != NULL) // si no es una lista vacía
	{
		last = ft_lstlast(*list); // encuentra el ultimo nodo
		if (last == *list)
		{
			// la lista tiene un solo elemento
			free((*list)->content);
			free(*list);
			*list = NULL;
		}
		else
		{
			// buscar el penúltimo nodo
			new_last = *list;
			while (new_last->next != last)
				new_last = new_last->next;
			new_last->next = NULL;
			// eliminar el último nodo
			free(last->content);
			free(last);
		}
	}
	return (*list);
}

t_list	*add_or_delete(t_list *list)
{
	t_list	*final_list;
	t_list	*new_node;
	char	*str;

	final_list = NULL;
	new_node = NULL;
	while (list != NULL)
	{
		str = list->content;
		new_node = create_node(str);
		ft_lstadd_back(&final_list, new_node);
		if ((!ft_strncmp(str, "..", 2) && ft_strlen(str) == 2) \
		|| (!ft_strncmp(str, ".", 1) && ft_strlen(str) == 1))
		{
			if (final_list != NULL)
			{
				remove_last_node(&final_list);
				remove_last_node(&final_list);
			}
		}
		list = list->next;
	}
	return (final_list);
}

char	*strjoin_list(t_list *list)
{
	char	*str;
	char	*temp;

	if (!list)
	return (NULL);
	str = (char *)malloc(sizeof(char) * 2);
	str = "/";
	while (list != NULL)
	{
		temp = ft_strjoin(str, list->content);
		str = temp;
		if (list->next != NULL)
		{
			temp = ft_strjoin(str, "/");
			str = temp;
		}
		list = list->next;
	}
	return (str);
}

char	*get_absolute_path(char *str)
{
	char	**path_splitted;
	t_list	*path_list;
	t_list	*final_list;

	if (!str)
		return (NULL);
	path_splitted = ft_split(str, '/');
	path_list = matrix_to_list(path_splitted);
	final_list = add_or_delete(path_list);
	str = strjoin_list(final_list);
	free_splitted(path_splitted);
	free_list(path_list);
	free_list(final_list);
	return (str);
}

/*
int main(int argc, char **argv)
{
	char	*str;
	(void)argc;

	str = get_absolute_path(argv[1]);
	printf("ruta absoluta %s\n", str);
	return (0);
}
*/
