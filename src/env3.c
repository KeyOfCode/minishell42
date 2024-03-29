/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/29 17:20:13 by darismen         ###   ########.fr       */
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
	ft_env_lstadd_back(data, node);
}

void	set_env(t_mini *data, char *name, char *value)
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
	if (flag && value != NULL)
	{
		if (current->equal == 0)
			current->equal = 1;
		current->val = value;
	}
}

	// if (current)
	// 	ft_env_add_or_replace(data, current);

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

char	*env_join(t_env *head)
{
	char	*val_tmp;
	char	*result;

	val_tmp = ft_strjoin("=", head->val);
	result = ft_strjoin(head->nm, val_tmp);
	free(val_tmp);
	return (result);
}
