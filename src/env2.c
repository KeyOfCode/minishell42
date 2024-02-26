/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/02/26 18:22:50 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_2rows_split(char *str)
{
	int		i;
	int		len;
	t_env	*node;

	i = -1;
	len = ft_strlen(str);
	node = calloc(1, sizeof(t_env));
	if (!str || len == 0 || !node)
		return (NULL);
	while (str[++i] && str[i] != '=')
		;
	node->nm = ft_substr(str, 0, i);
	if (!node->nm)
		return (free(&node), NULL);
	if (str[i] == '=' && i < len - 1)
	{
		node->val = ft_substr(str, i + 1, len - i - 1);
		node->equal = 1;
		return (node);
	}
	node->val = 0;
	node->equal = 0;
	return (node);
}

void	ft_add_envp(t_mini *data, char **envp)
{
	int		i;
	t_env	*node;

	i = -1;
	while (envp[++i])
	{
		node = ft_2rows_split(envp[i]);
		node->next = NULL;
		if (!node)
			return ;
		if (ft_env_forbidden_chars(node->nm, ft_strlen(node->nm)))
		{
			printf("export: '%s': not a valid identifier\n", node->nm);
			free(node);
			return ;
		}
		ft_env_add_or_replace(data, node);
	}
}

void	ft_dup_envp(t_mini *data, char **envp)
{
	int		i;
	t_env	*node;

	i = -1;
	while (envp[++i])
	{
		node = ft_2rows_split(envp[i]);
		node->next = NULL;
		if (!node)
			return ;
		if (ft_env_forbidden_chars(node->nm, ft_strlen(node->nm)))
		{
			printf("export: '%s': not a valid identifier\n", node->nm);
			free (node);
			return ;
		}
		if (ft_strncmp(node->nm, "OLDPWD", ft_strlen(node->nm)) == 0)
			node->val = NULL;
		ft_env_lstadd_back(data, node);
	}
}

/* void	set_env(t_mini *data, char *name, char *value)
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
	if (flag)
	{
		current->val = value;
		// return (1);
	}
	// return (0);
}

char	*get_env(t_mini *data, char *name)
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
	if (flag)
		return (current->val);
	return (0);
}
 */