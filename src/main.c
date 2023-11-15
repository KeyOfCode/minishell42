/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/11/15 20:47:06 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	free_mini();
}

/* void	parser(char *argv)
{
}

void	lexer(char	*argv)
{
} */

void	ft_prompt(t_mini *data)
{
	char	*line;

	line = "";
	line = readline("minishell $ ");
	if (line[0] != '\0')
	{
		printf("%s\n", line);
		add_history(line);
		ft_lexer(data);
		ft_parser(data);
	}
	free(line);
}

// int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_mini	data;

	// (void)argv;
	// if (argc > 1)
	// 	ft_error("Arg Error.");
	// ft_duplicate_envp(&data, envp);
	while (1)
	{
		ft_prompt(&data);
	}
}
