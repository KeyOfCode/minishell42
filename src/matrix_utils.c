/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/24 20:32:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
