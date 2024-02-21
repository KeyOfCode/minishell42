/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/02/16 20:06:37 by darismen         ###   ########.fr       */
=======
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/02/19 18:53:36 by disantam         ###   ########.fr       */
>>>>>>> 90cc80e0674ed058135f735c18aa4ad96a0c3e8a
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
=======
int	g_status;

>>>>>>> 90cc80e0674ed058135f735c18aa4ad96a0c3e8a
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_error(char *err_msg)
{
<<<<<<< HEAD
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_SUCCESS);
=======
	g_status = 1;
	ft_putendl_fd(err_msg, 2);
>>>>>>> 90cc80e0674ed058135f735c18aa4ad96a0c3e8a
}

void	ft_print_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
<<<<<<< HEAD
		printf("&%s--\n", splits[i]);
=======
		ft_putstr_fd("&", 2);
		ft_putstr_fd(splits[i], 2);
		ft_putstr_fd("\n", 2);
>>>>>>> 90cc80e0674ed058135f735c18aa4ad96a0c3e8a
		i++;
	}
}

<<<<<<< HEAD
void	ft_ctrl_d(t_mini *data)
{
	if (!data->prompt)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		clear_history();
		ft_free_data(data);
		// ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS);
	}
}

void	ft_free_matrix(char **newarry)
{
	int	i;

	i = 0;
	if (!newarry)
		return ;
	while (newarry[i])
	{
		free(newarry[i]);
		i++;
	}
	free(newarry);
}
=======
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		rl_redisplay();
		ft_putstr_fd("  \n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	ft_ctrl_d(t_mini *data)
// {
// 	if (!data->prompt)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 		ft_putstr_fd("exit\n", STDOUT_FILENO);
// 		clear_history();
// 		ft_env_lstclear(data->env_lst);
// 		exit(g_status);
// 	}
// }
>>>>>>> 90cc80e0674ed058135f735c18aa4ad96a0c3e8a
