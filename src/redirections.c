/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/02/21 15:40:11 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	input_redir(t_cmd *cmd, char **token)
{
	
} */

int	input_redir(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	// if (!cmd)
	// 	return ;
	// if (cmd->fd[READ_END] != STDIN_FILENO)
	// 	close(cmd->fd[READ_END]);
	// (void)fd;
	fd_path = NULL;
	if (token[1] != NULL)
	{
		fd_path = ft_strdup(token[1]);
	}
	if (!fd_path)
	{
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	}
	ft_putstr_fd("file:", 2);
	ft_putstr_fd(fd_path, 2);
	ft_putstr_fd("\n", 2);
	fd = open(fd_path, O_RDONLY);
	if (cmd->fd[READ_END] < 0)
	{
		return (ft_error("bash: test: No such file or directory"), 127);
	}
	cmd->fd[READ_END] = fd;
	dup2(cmd->fd[READ_END], STDIN_FILENO);
	close(cmd->fd[READ_END]);
	free(fd_path);
	return (0);
}

int	output_redir(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	// if (!cmd)
	// 	return (1);
	// if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	// 	close(cmd->fd[WRITE_END]);
	fd_path = NULL;
	if (token[1] != NULL)
	{
		fd_path = ft_strdup(token[1]);
		ft_putstr_fd("file:", 2);
		ft_putstr_fd(fd_path, 2);
		ft_putstr_fd("\n", 2);
	}
	if (!fd_path)
	{
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	}
	fd = open(fd_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(fd_path);
	if (fd < 0)
	{
		return (ft_error("bash: test: No such file or directory"), 127);
	}
	cmd->fd[WRITE_END] = fd;
	dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
	close(cmd->fd[WRITE_END]);
	return (0);
}

int	output_redir_append(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	if (!cmd)
		return (1);
	if (cmd->fd[WRITE_END] != STDOUT_FILENO)
		close(cmd->fd[WRITE_END]);
	fd_path = NULL;
	if (token[1] != NULL)
		fd_path = ft_strdup(token[1]);
	if (!fd_path)
	{
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	}
	fd = open(fd_path, O_CREAT | O_APPEND | O_RDWR, 0644);
	free(fd_path);
	if (fd < 0)
	{
		return (ft_error("bash: test: No such file or directory"), 127);
	}
	cmd->fd[WRITE_END] = fd;
	dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
	close(cmd->fd[WRITE_END]);
	return (0);
}

/**
 * 
 */
int	input_heredoc(t_cmd *cmd, char **token)
{
	(void)cmd;
	(void)token;
/* 	char	*fd_path;
	char	*aux;
	char	*temp;
	char	*str;
	int		fd;

	if (!cmd)
		return ;
	str = NULL;
	temp = NULL;
	while (ft_strncmp(temp, token, ft_strlen(token)))
	{
		str = readline("> $ ");
		aux = ft_strjoin(temp, str);
		temp = aux;
	} */
	return (0);
}

int	input_redir(t_cmd *cmd, char **token);
int	input_heredoc(t_cmd *cmd, char **token);
int	output_redir(t_cmd *cmd, char **token);
int	output_redir_append(t_cmd *cmd, char **token);