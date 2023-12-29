/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/29 15:11:59 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lexer(t_mini *data)
{
	char	**trim;
	int		i;

	i = -1;
	if (!data->prompt)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
	data->full_cmd = ft_cmdtrim(data->prompt);
	if (!data->full_cmd)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
	ft_expander(data);
	ft_cmdlst(data);
	trim = data->full_cmd;
	ft_print_splits(trim);
	free(trim);
}

// void	ft_free_data(t_mini *data)
// {
// }

void	ft_prompt(t_mini *data)
{
	data->prompt = readline("minishell $ ");
	if (data->prompt[0] != '\0')
	{
		add_history(data->prompt);
		ft_lexer(data);
		// ft_parser(data);
	}
	free(data->prompt);
	// ft_free_data(data);
}

void	ft_init_data(t_mini *data)
{
	data->prompt = NULL;
	data->cmd_list = NULL;
	data->env_lst = NULL;
	data->envp = NULL;
	data->full_cmd = NULL;
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
	data.envp = envp;
	ft_dup_envp(&data, envp);
	if (!data.envp)
		ft_error("Env Error.");
	while (1)
	{
		ft_prompt(&data);
	}
}
