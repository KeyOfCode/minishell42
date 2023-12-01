/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:26:33 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/30 18:43:06 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	main(int argc, char **argv)
{
	char	*file;
	char	*full_path;

	if (argc == 2)
	{
		file = &argv[1][0];
		full_path = get_full_path(file);
		if (full_path != NULL)
		{
			printf("Path completo para %s:\n %s\n", file, full_path);
			free(full_path);
		}
	}
	return (0);
}

/*

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
	   printf("Current working dir: %s\n", cwd);
   } else {
	   perror("getcwd() error");
	   return 1;
   }
   return 0;
}

*/