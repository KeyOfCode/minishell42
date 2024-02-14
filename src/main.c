/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/01/29 18:02:04 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_print_nodes(t_cmd **cmd_lst)
// {
// 	t_cmd	*cmd;
// 	int		j;
// 	int		i;

// 	cmd = *cmd_lst;
// 	i = 1;
// 	while (cmd)
// 	{
// 		printf("node %d:\n", i);
// 		printf("\tc_args: \n");
// 		j = -1;
// 		while (cmd->c_args[++j])
// 			printf("\t\t%s--\n", cmd->c_args[j]);
// 		printf("\n\tc_abs_path: %s\n", cmd->c_args[0]);
// 		i++;
// 		cmd = cmd->next;
// 	}
// }

void	ft_lexer(t_mini *data)
{
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
	char	**trim;
	trim = data->full_cmd;
	ft_print_splits(trim);
	free(trim);
	// ft_print_nodes(data->cmd_lst);
}
	// char	**trim;
	// trim = data->full_cmd;
	// ft_print_splits(trim);
	// free(trim);
// void	ft_free_data(t_mini *data)
// {
// }

void	ft_prompt(t_mini *data)
{
	data->prompt = readline("minishell $ ");
	ft_ctrl_d(data);
	if (data->prompt[0] != '\0')
	{
		add_history(data->prompt);
		ft_lexer(data);
		ft_parser(data);
	}
	free(data->prompt);
	// ft_free_data(data);
}

void	ft_init_data(t_mini *data)
{
	data->prompt = NULL;
	data->cmd_lst = NULL;
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
	if (!data.envp)
		ft_error("Env Error.");
	ft_dup_envp(&data, envp);
	while (1)
	{
		ft_prompt(&data);
	}
}
