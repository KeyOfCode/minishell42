/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:18 by darismen          #+#    #+#             */
/*   Updated: 2024/01/24 19:17:46 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_error(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	ft_print_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		printf("&%s--\n", splits[i]);
		i++;
	}
}
