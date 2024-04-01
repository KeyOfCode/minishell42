/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/04/01 20:41:36 by darismen         ###   ########.fr       */
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
	node = ft_calloc(1, sizeof(t_env));
	if (!str || len == 0 || !node)
		return (NULL);
	while (str[++i] && str[i] != '=')
		;
	node->nm = ft_substr(str, 0, i);
	if (!node->nm)
		return (free(node), NULL);
	if (str[i] == '=' && i < len - 1)
	{
		node->val = ft_substr(str, i + 1, len - i - 1);
		node->equal = 1;
		return (node);
	}
	node->val = NULL;
	node->equal = 0;
	return (node);
}

void	ft_add_envp(t_mini *data, char *arg)
{
	int		i;
	t_env	*node;

	i = -1;
	node = ft_2rows_split(arg);
	if (!node)
		return ;
	node->next = NULL;
	if (ft_env_forbidden_chars(node->nm, ft_strlen(node->nm)))
	{
		ft_error("export: '%s': not a valid identifier\n", node->nm);
		free(node);
		return ;
	}
	if (env_exist(data, arg))
		set_env(data, arg, node->val);
	else
		ft_env_lstadd_back(data, node);
}

void	ft_dup_envp(t_mini *data, char **envp)
{
	int		i;
	t_env	*node;

	i = -1;
	while (envp[++i])
	{
		node = ft_2rows_split(envp[i]);
		if (!node)
			return ;
		node->next = NULL;
		if (ft_env_forbidden_chars(node->nm, ft_strlen(node->nm)))
			return (ft_error("export: '%s': not a valid \
identifier\n", node->nm), ft_delnode(node));
		if (ft_strncmp(node->nm, "OLDPWD", 6) == 0)
		{
			free(node->val);
			node->val = NULL;
			node->equal = 0;
		}
		ft_env_lstadd_back(data, node);
	}
	if (!env_exist(data, "OLDPWD"))
		ft_add_oldpwd(data);
}

char	**ft_dup_matrix(char **matrix)
{
	int		i;
	char	**new;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	new = ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (matrix[++i] != NULL)
	{
		new[i] = ft_strdup(matrix[i]);
	}
	return (new);
}

void	ft_delnode(t_env *del)
{
	free(del->nm);
	if (del->val)
		free(del->val);
	free(del);
}
