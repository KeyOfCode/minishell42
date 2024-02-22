/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/02/22 17:02:31 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redir(t_cmd *cmd, char **token)
{
	int		fd;

	// if (cmd->fd[READ_END] != STDIN_FILENO)
	// 	close(cmd->fd[READ_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	if (isredir(token[1]) || !ft_strncmp(token[1], "|", 1))
	{
		return (redir_error(token[1]), 1);
	}
	ft_putstr_fd("file:", 2);
	ft_putstr_fd(token[1], 2);
	ft_putstr_fd("\n", 2);
	fd = open(token[1], O_RDONLY);
	if (fd < 0)
	{
		return (ft_error("bash: test: No such file or directory"), 127);
	}
	cmd->fd[READ_END] = fd;
	dup2(cmd->fd[READ_END], STDIN_FILENO);
	close(cmd->fd[READ_END]);
	return (0);
}

int	output_redir(t_cmd *cmd, char **token)
{
	int		fd;

	// if (cmd->fd[WRITE_END] != STDOUT_FILENO)
	// 	close(cmd->fd[WRITE_END]);
if (token[1] == NULL)
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	if (isredir(token[1]) || !ft_strncmp(token[1], "|", 1))
	{
		return (redir_error(token[1]), 1);
	}
	ft_putstr_fd("file:", 2);
	ft_putstr_fd(token[1], 2);
	ft_putstr_fd("\n", 2);
	fd = open(token[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
	int		fd;

	if (cmd->fd[WRITE_END] != STDOUT_FILENO)
		close(cmd->fd[WRITE_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near unexpected token `newline\'"), 1);
	if (isredir(token[1]) || !ft_strncmp(token[1], "|", 1))
	{
		return (redir_error(token[1]), 1);
	}
	ft_putstr_fd("file:", 2);
	ft_putstr_fd(token[1], 2);
	ft_putstr_fd("\n", 2);
	fd = open(token[1], O_CREAT | O_APPEND | O_RDWR, 0644);
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