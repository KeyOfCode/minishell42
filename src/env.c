/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/24 20:28:48 by darismen         ###   ########.fr       */
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
	node = (t_env *)malloc(sizeof(t_env));
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
			printf("export: `%s': not a valid identifier\n", node->nm);
			free (node);
			return ;
		}
		if (ft_strncmp(node->nm, "OLDPWD", ft_strlen(node->nm)) == 0)
			node->val = NULL;
		ft_env_lstadd_back(data, node);
	}
}

/* char	**ft_2rows_split(char *str, char c)
{
	size_t	i;
	int		len;
	char	**matrix;

	i = -1;
	len = ft_strlen(str);
	matrix = ft_calloc(3, sizeof(char *));
	if (!str || len == 0)
		return (NULL);
	if (!matrix)
		return (NULL);
	while (str[++i] && str[i] != '=')
		;
	matrix[0] = ft_substr(str, 0, i);
	if (!matrix[0])
		return (free(matrix), NULL);
	if (str[i] == '=' && i < len - 1)
	{
		matrix[1] = ft_substr(str, i + 1, len - i - 1);
		if (!matrix[1])
			return (free(matrix), NULL);
	}
	else if (str[i] != '=' || (str[i] == '=' && i == len - 1))
		matrix[1] = ft_calloc(1, sizeof(char));
	return (matrix);
} */

/* char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	return (NULL);
} */

/* char	**env_lst(t_mini *data, char**matrix, int mode)
{
	int		i;
	t_env	node;
	char	**env;

	i = -1;
	env = data->envp;
	if (mode == 1)
	{
	}
	// node = ft_calloc(3, sizeof(t_env));
	while (env[++i] && env[i] != '=')
		;
	node.nm = ft_substr(env, 0, i);
	if (!node.nm)
		exit(EXIT_FAILURE);
	if (env[i] == c && i < ft_strlen(env))
} */
