/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/14 17:39:11 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_forbidden_chars(char *name, int len)
{
	int	i;

	i = 0;
	if (!(ft_isupper(name[i]) || ft_islower(name[i]) || (name[i] == '_')))
		return (1);
	while (i < len && name[++i])
	{
		if (!(ft_isupper(name[i]) || ft_islower(name[i])
				|| ft_isdigit(name[i]) || (name[i] == '_')))
			return (1);
	}
	return (0);
}

void	ft_env_add_or_replace(t_mini *data, t_env *new)
{
	t_env	*current;
	t_env	*replace;
	int		flag;

	flag = 0;
	if (!data->env_lst)
	{
		data->env_lst = new;
		return ;
	}
	current = data->env_lst;
	while (current->next && !flag)
	{
		if (!ft_strncmp(current->next->nm, new->nm,
				ft_strlen(current->next->nm)))
			flag = 1;
		else
			current = current->next;
	}
	replace = current;
	if (flag)
		new->next = replace->next->next;
	replace->next = new;
} 

void	ft_env_lstadd_back(t_mini *data, t_env *new)
{
	t_env	*last_elem;
	t_env	*current;

	if (!data->env_lst)
	{
		data->env_lst = new;
		return ;
	}
	current = data->env_lst;
	while (current->next)
		current = current->next;
	last_elem = current;
	last_elem->next = new;
}

void	ft_env_remove(t_mini *data, char *str)
{
	t_env	*head;
	t_env	*del;

	head = data->env_lst;
	if (str[0] == '~')
		str = "$HOME";
	if (!ft_strncmp(head->nm, str, ft_strlen(head->nm)))
	{
		del = head->next;
		head = del->next;
		ft_delnode(del);
		return ;
	}
	while (head->next)
	{
		if (!ft_strncmp(head->next->nm, str,
				ft_strlen(head->next->nm)))
		{
			del = head->next;
			head->next = del->next;
			ft_delnode(del);
			return ;
		}
		head = head->next;
	}
}

void	ft_env_lstclear(t_env *env)
{
	t_env	*del_node;
	t_env	*head;

	head = env;
	if (head == NULL)
		return ;
	while (head)
	{
		del_node = head;
		head = del_node->next;
		ft_delnode(del_node);
	}
}
