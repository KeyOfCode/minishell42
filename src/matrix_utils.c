/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/01 19:44:14 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	dup_matrix(t_mini *data, char **matrix)
{
	int		i;
	int		rows;
	char	**dup_matrix;

	if (!matrix)
		return ;
	rows = 0;
	i = 0;
	while (matrix[i++] != NULL)
		rows++;
	dup_matrix = (char **)malloc((rows + 1) * sizeof(char *));
	if (!dup_matrix)
		return ;
	i = 0;
	while (i < rows)
	{
		dup_matrix[i] = ft_strdup(matrix[i]);
		if (!dup_matrix[i++])
		{
			free_matrix(dup_matrix);
			return ;
		}
	}
	dup_matrix[rows] = NULL;
	data->envp = dup_matrix;
}
