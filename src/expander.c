/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/04 19:43:24 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_absolute_path(char *str)
{
	char	**path_splitted;
	t_list	*path_list;
	t_list	*final_list;

	if (!str)
		return (NULL);
	path_splitted = ft_split(str, '/');
	path_list = matrix_to_list(path_splitted);
	final_list = add_or_delete(path_list);
	str = strjoin_list(final_list);
	free_matrix(path_splitted);
	free_list(path_list);
	free_list(final_list);
	return (str);
}

char	*get_full_path(char *file)
{
	char	current_directory[PATH_MAX];
	char	*absolute_path;
	char	*file_path;
	char	*full_path;

	absolute_path = NULL;
	file_path = NULL;
	full_path = NULL;
	if (file != NULL)
	{
		if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		{
			printf("current directory: %s\n", current_directory);
			absolute_path = get_absolute_path(current_directory);
			if (file[0] != '/') // Si file es una ruta relativa
			{
				absolute_path = ft_strjoin(absolute_path, "/");
				file_path = ft_strjoin(absolute_path, file);
				printf("file path: %s\n", file_path);
				full_path = get_absolute_path(file_path);
			}
			else // si es una ruta absoluta (incluso con navegacion)
				full_path = absolute_path;
		}
	}
	return (full_path);
}

char	*expand_env(char *search, char **env)
{
	int		search_len;
	char	*expanded;
	int		i;

	if (!search || !env)
		return (NULL);
	if (search[0] == '~' && ft_strlen(search) == 1)
		search = "$HOME";
	search++;
	search_len = ft_strlen(search);
	expanded = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], search, search_len) == 0)
		{
			if (env[i][search_len] == '=' || env[i][search_len] == '\0')
			{
				expanded = env[i] + search_len + 1;
				break ;
			}
		}
		i++;
	}
	return (expanded);
}

void	ft_expander(t_mini *data)
{
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	while (data->full_cmd[i])
	{
		j = 0;
		while (data->full_cmd[i][j] != '\0')
		{
			if (data->full_cmd[i][j] == '\'')
				while (data->full_cmd[i][j] != '\'')
					j++;
			if (ft_strchr("$~", data->full_cmd[i][j]))
			{
				expanded = expand_env(data->full_cmd[i], data->envp);
				data->full_cmd[i] = expanded;
			}
			j++;
		}
		printf("%s\n", expanded);
		i++;
	}
}
