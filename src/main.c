/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/11/29 18:48:23 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lexer(char *line)
{
	char	**trim;

	trim = ft_cmdtrim(line);
	ft_print_splits(trim);
	// ft_expander(trim);
	// trim = ft_cmdsubsplit(trim);
	free(trim);
}

// void	ft_dup_envp(t_mini *data, char **envp)
// {
// }

void	ft_prompt(t_mini *data)
{
	char	*line;

	line = "";
	(void)data;
	line = readline("minishell $ ");
	if (line[0] != '\0')
	{
		//printf("%s\n", line);
		add_history(line);
		ft_lexer(line);
	}
	free(line);
}

/**
 * @brief main
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)argv;
	if (argc > 1)
		ft_error("Arg Error.");
	(void)envp;
	// ft_dup_envp(&data, envp);
	while (1)
	{
		ft_prompt(&data);
	}
}
