/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/11/13 19:05:38 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	parser(char *argv)
{
}

void	lexer(char	*argv)
{
} */

void	prompt(void)
{
	char	*line;

	line = "";
	while (1)
	{
		line = readline("minishell $ ");
		if (line != NULL)
			printf("%s\n", line);
		else
			break ;
		add_history(line);
	}
	free(line);
}

int	main(void)
{
	prompt();
}
