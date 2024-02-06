/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/20 17:01:54 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**free_matrix(char **matrix)
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
}

char	**dup_matrix(char **matrix)
{
	int		i;
	int		rows;
	char	**dup_matrix;

	if (!matrix)
		return (NULL);
	rows = 0;
	while (*matrix != NULL)
	{
		matrix++;
		rows++;
	}
	dup_matrix = (char **)malloc((rows + 1) * sizeof(char *));
	if (!dup_matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dup_matrix[i] = ft_strdup(matrix[i]);
		if (!dup_matrix[i])
		{
			free_matrix(dup_matrix);
			return (NULL);
		}
		i++;
	}
	dup_matrix[rows] = NULL;
	return (dup_matrix);
}
