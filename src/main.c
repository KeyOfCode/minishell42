/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/06 18:07:31 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lexer(t_mini *data)
{
	char	**trim;

	data->full_cmd = ft_cmdtrim(data->cmdline);
	ft_expander(data);
	trim = data->full_cmd;
	ft_print_splits(trim);
	free(trim);
}

// void	ft_dup_envp(t_mini *data, char **envp)
// {
// }

void	ft_prompt(t_mini *data)
{
	data->cmdline = readline("minishell $ ");
	if (data->cmdline[0] != '\0')
	{
		add_history(data->cmdline);
		ft_lexer(data);
	}
	free(data->cmdline);
}

void	ft_init_data(t_mini *data)
{
	data->full_cmd = NULL;
	data->cmdline = NULL;
	data->envp = NULL;
	data->full_path = NULL;
}

/**
 * @brief main
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 */
int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)argv;
	if (argc > 1)
		ft_error("Arg Error.");
	ft_init_data(&data);
	dup_matrix(&data, envp);
	if (!data.envp)
		ft_error("Env Error.");
	while (1)
	{
		ft_prompt(&data);
	}
}
