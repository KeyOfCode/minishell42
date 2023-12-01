/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:39:43 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/30 18:51:18 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
Esta función recibe dos argumentos de entrada:
-	un string a expandir:
		que comienza por '$' de la variable de entorno (ejemplo: $PWD)
		ó '~' que se sustituye por la variable de entorno $HOME
-	una matriz con las variables de entorno del sistema
*/

char	*expand_env(const char *search, char **env)
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
		if (ft_strncmp((const char *)env[i], search, search_len) == 0)
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

/*
int	main(int argc, char **argv, char **env)
{
	char	*to_find;

	if (argc != 2)
		return (EXIT_FAILURE);
	to_find = &argv[1][0];
	printf("environment variable required: %s\n", to_find);
	if (!expand_env(to_find, env))
	{
		printf("error: environment variable not found\n");
		return (EXIT_FAILURE);
	}
	else
		printf("environment variable expanded: %s\n", expand_env(to_find, env));
	return (0);
}
*/
