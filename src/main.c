/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/22 12:03:02 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_lexer(t_mini *data)
{
	int		i;

	i = -1;
	data->full_cmd = ft_cmdtrim(data->prompt);
	if (!data->full_cmd)
	{
		g_status = 1;
		return (NULL);
	}
	ft_expander(data);
	if (!ft_cmdlst(data))
	{
		g_status = 1;
		return (NULL);
	}
	return (data);
}

void	ft_prompt(t_mini *data)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data->prompt = readline("minishell $ ");
	if (!data->prompt)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("exit\n");
		ft_mini_exit(data, 0);
	}
	if (data->prompt[0] != '\0')
	{
		add_history(data->prompt);
		if (ft_lexer(data) != NULL)
			g_status = ft_parser(data);
	}
	free(data->prompt);
}

void	ft_init_data(t_mini *data)
{
	data->prompt = NULL;
	data->dquote = 0;
	data->squote = 0;
	data->cmd_lst = NULL;
	data->env_lst = NULL;
	data->envp = NULL;
	data->full_cmd = NULL;
	data->full_path = NULL;
	data->fd[READ_END] = (STDIN_FILENO);
	data->fd[WRITE_END] = (STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	g_status = 0;
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

	if (argc > 1)
	{
		return (ft_error("Arg Error.\n", NULL), 1);
	}
	ft_init_data(&data);
	data.envp = ft_dup_matrix(envp);
	if (!data.envp)
	{
		return (ft_error("Env Error.\n", NULL), 1);
	}
	ft_dup_envp(&data, envp);
	while (argv)
	{
		ft_prompt(&data);
	}
	return (0);
}
