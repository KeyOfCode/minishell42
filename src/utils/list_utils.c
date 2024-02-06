/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:57:36 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/30 18:43:26 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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