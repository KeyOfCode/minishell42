/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:42:59 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/08 14:58:25 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_redir(t_child *childs, char **tokens)
{
	int		fd;
	char	*fd_path;
	t_child	*last_node;

	if (!childs|| !tokens)
		return ;
	fd_path = ft_strdup(tokens++);// obtener la nueva ruta para el fd: tokens++
	if (!fd_path)
	{
		// Error
		return ;
	}
	fd = open(fd_path, O_RDONLY);
	free(fd_path);
	if (fd < 0)
	{
		// Error
	}
	last_node = get_last_child(childs);
	last_node->infile = fd;// cambiar child->infile por el nuevo fd
}

void	output_redir(t_child *childs, char **tokens)
{
	int		fd;
	char	*fd_path;
	t_child	*last_node;

	if (!childs|| !tokens)
		return ;
	// obtener la nueva ruta para el fd: tokens++
	fd_path = ft_strdup(tokens++);
	if (!fd_path)
	{
		// Error
		return ;
	}
	fd = open(fd_path, O_WRONLY | O_CREAT, 0644);
	free(fd_path);
	if (fd < 0)
	{
		// Error
	}
	last_node = get_last_child(childs);
	last_node->outfile = fd;// cambiar child->outfile por el nuevo fd
}

void	output_redir_append(t_child *childs, char **tokens)
{
	int		fd;
	char	*fd_path;
	t_child	*last_node;

	if (!childs || !tokens)
		return ;
	tokens++;
	fd_path = ft_strdup(tokens++); // obtener la nueva ruta para el fd: tokens++
	if (!fd_path)
	{
		// Error
		return ;
	}
	fd = open(fd_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(fd_path);
	if (fd < 0)
	{
		// Error
	}
	last_node = get_last_child(childs);
	last_node->outfile = fd;// cambiar child->outfile por el nuevo fd
}
