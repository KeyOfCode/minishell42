/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/02/14 19:14:47 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	input_redir(t_cmd *cmd, char **token)
{
	
} */

void	input_redir(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	// if (!cmd)
	// 	return ;
	// if (cmd->fd[READ_END] != STDIN_FILENO)
	// 	close(cmd->fd[READ_END]);
	(void)fd;
	fd_path = ft_strdup(token[1]);
	printf("file: %s\n\n", fd_path);
	if (!fd_path)
	{
		ft_error("bash: syntax error near unexpected token `newline\'");
		return ;
	}
	cmd->fd[READ_END] = dup(open(fd_path, O_RDONLY));
	if (cmd->fd[READ_END] < 0)
	{
		ft_error("bash: test: No such file or directory");
	}
	else
	{
		dup2(open(fd_path, O_RDONLY), STDIN_FILENO);
		close(cmd->fd[READ_END]);
	}
	free(fd_path);
}

void	output_redir(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	if (!cmd)
		return ;
	// if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	// 	close(cmd->fd[WRITE_END]);
	fd_path = ft_strdup(token[1]);
	printf("file: %s\n\n", fd_path);
	if (!fd_path)
	{
		ft_error("bash: syntax error near unexpected token `newline\'");
		return ;
	}
	fd = open(fd_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(fd_path);
	if (fd < 0)
	{
		ft_error("bash: test: No such file or directory");
	}
	else
	{
		cmd->fd[WRITE_END] = fd;
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
}

void	output_redir_append(t_cmd *cmd, char **token)
{
	char	*fd_path;
	int		fd;

	if (!cmd)
		return ;
	if (cmd->fd[WRITE_END] != STDOUT_FILENO)
		close(cmd->fd[WRITE_END]);
	fd_path = ft_strdup(token[1]);
	if (!fd_path)
	{
		ft_error("bash: syntax error near unexpected token `newline\'");
		return ;
	}
	fd = open(fd_path, O_CREAT | O_APPEND | O_RDWR, 0644);
	free(fd_path);
	if (fd < 0)
		ft_error("bash: test: No such file or directory");
	else
	{
		cmd->fd[WRITE_END] = fd;
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
}

/**
 * 
 */
void	input_heredoc(t_cmd *cmd, char **token)
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
}

void	input_redir(t_cmd *cmd, char **token);
void	input_heredoc(t_cmd *cmd, char **token);
void	output_redir(t_cmd *cmd, char **token);
void	output_redir_append(t_cmd *cmd, char **token);