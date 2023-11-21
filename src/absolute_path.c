/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:13:56 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/20 21:31:24 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_node(char *str)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new || !str)
		return (NULL);
	new->content = ft_strdup(str);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	print_list(t_list *list)
{
	while (list != NULL)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

void	free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	if (list == NULL)
		return ;
	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
	}
}

char	**free_splitted(char **splitted)
{
	int	i;

	i = 0;
	if (splitted != NULL)
	{
		while (splitted[i] != NULL)
		{
			free(splitted[i]);
			i++;
		}
		free(splitted);
	}
	return (NULL);
}

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

t_list	*matrix_to_list(char **str)
{
	char	*line;
	t_list	*begin_list;
	t_list	*to_add;

	line = NULL;
	begin_list = NULL;
	to_add = NULL;
	if (str)
	{
		while (*str != NULL)
		{
			line = *str;
			to_add = create_node(line);
			ft_lstadd_back(&begin_list, to_add);
			str++;
		}
	}
	return (begin_list);
}

char	*strjoin_list(t_list *list)
{
	char	*str;
	char	*temp;

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

t_list	*dup_list(t_list *list)
{
	char	*str;
	t_list	*new_list;
	t_list	*to_add;

	str = NULL;
	new_list = NULL;
	to_add = NULL;
	if (list != NULL)
	{
		while (list != NULL)
		{
			str = list->content;
			to_add = create_node(str);
			ft_lstadd_back(&new_list, to_add);
			list = list->next;
		}
	}
	return (new_list);
}

char	*get_absolute_path(char *str)
{
	char	**path_splitted;
	t_list	*path_list;
	t_list	*final_list;

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
