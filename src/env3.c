/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/04/01 21:03:36 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_oldpwd(t_mini *data)
{
	t_env	*node;

	node = ft_2rows_split("OLDPWD");
	if (!node)
	{
		return ;
	}
	node->next = NULL;
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
	if (flag)
	{
		if (current->equal == 0)
			current->equal = 1;
		if (current->val)
			free(current->val);
		if (value == NULL)
			current->val = "";
		else
			current->val = ft_strdup(value);
	}
}

int	env_exist(t_mini *data, char *name)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && flag == 0)
	{
		if (!ft_strncmp(current->nm, name, ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag)
		return (1);
	return (0);
}

char	*get_env(t_mini *data, char *name)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = data->env_lst;
	while (current && flag == 0)
	{
		if (!ft_strncmp(current->nm, name, ft_strlen(current->nm)))
			flag = 1;
		else
			current = current->next;
	}
	if (flag && current->val)
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
