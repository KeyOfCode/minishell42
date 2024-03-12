/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/12 17:32:33 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_lexer(t_mini *data)
{
	int		i;
	char	**trim;

	i = -1;
	data->full_cmd = ft_cmdtrim(data->prompt);
	if (!data->full_cmd)
	{
		g_status.exit_code = 1;
		return (NULL);
	}
	ft_expander(data);
	if (!ft_cmdlst(data))
	{
		g_status.exit_code = 1;
		return (NULL);
	}
	trim = data->full_cmd;
	ft_print_splits(trim);
	free(trim);
	return (data);
	// ft_print_nodes(data->cmd_lst);
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
		ft_mini_exit(data);
	}
	// ft_ctrl_d(data);
	if (data->prompt[0] != '\0')
	{
		add_history(data->prompt);
		if (ft_lexer(data) != NULL)
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
	data->fd[READ_END] = (STDIN_FILENO);
	data->fd[WRITE_END] = (STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	g_status = 0;
	data->pid = 0;
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
		return (ft_error("Arg Error.\n", NULL), 1);
	ft_init_data(&data);
	data.envp = envp;
	if (!data.envp)
		return (ft_error("Env Error.\n", NULL), 1);
	ft_dup_envp(&data, envp);
	while (1)
	{
		ft_prompt(&data);
	}
	return (0);
}
