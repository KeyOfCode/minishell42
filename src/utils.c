/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/03/29 17:17:36 by darismen         ###   ########.fr       */
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
			{
				ft_putstr_fd(type, 2);
			}
			i += 1;
		}
		else
		{
			ft_putchar_fd(str[i], 2);
		}
		i++;
	}
	g_status = 1;
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
	{
		return (1);
	}
	else
	{
		return (0);
	}
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

char	*ft_join_free(char *s1, char *s2, int f)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	if (f >= 1)
		free(s1);
	if (f >= 2)
		free(s2);
	return (aux);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_redisplay();
		rl_replace_line("", 0);
		printf("  \n");
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
}

		// rl_redisplay();
		// rl_replace_line("", 0);
		// printf("  \n");
		// rl_on_new_line();
		// rl_redisplay();
		// g_status = 130;