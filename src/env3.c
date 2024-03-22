/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/21 14:46:19 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_oldpwd(t_mini *data)
{
	t_env	*node;

	node = ft_2rows_split("OLDPWD");
	node->next = NULL;
	if (!node)
	{
		return ;
	}
	node->equal = 0;
	node->val = 0;
	ft_env_add_or_replace(data, node);
}

void	set_env(t_mini *data, char *name, char *value)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && !flag)
	{
		if (!ft_strncmp(current->nm, name,
				ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag && value != NULL)
	{
		if (current->equal == 0)
			current->equal = 1;
		current->val = ft_strdup(value);
	}
	if (current)
		ft_env_add_or_replace(data, current);
}

char	*get_env(t_mini *data, char *name)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && !flag)
	{
		if (!ft_strncmp(current->nm, name, ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag)
		return (current->val);
	return (NULL);
}
