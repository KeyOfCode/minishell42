/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/12 17:40:24 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

void	ft_error(char const *str, char *type)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && type != NULL)
		{
			if (str[i + 1] == 's')
				ft_putstr_fd(type, 2);
			i += 1;
		}
		else
			ft_putchar_fd(str[i], 2);
		i++;
	}
	g_status = 1;
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_print_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		ft_putstr_fd("&", 2);
		ft_putstr_fd(splits[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

char	*ft_join_free(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	return (aux);
}

void	handle_sigint(int sig)
{
	// if (g_status.pid != 0 && g_status.pid != -1)
	// {
	// 	printf("\n");
	// 	kill(g_status.pid, SIGKILL);
	// 	g_status.exit_code = 130;
	// 	g_status.pid = 0;
	// }
	if (sig == SIGINT)
	{
		rl_redisplay();
		printf("  \n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

