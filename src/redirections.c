/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/04/01 21:18:20 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[READ_END] != -1)
		close(cmd->fd[READ_END]);
	cmd->fd[READ_END] = open(token[1], O_RDONLY);
	if (cmd->fd[READ_END] < 0)
	{
		return (ft_error("minishell: %s: No such file or directory\n",
				token[1]), 127);
	}
	return (0);
}

int	output_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[WRITE_END] != -1)
		close(cmd->fd[WRITE_END]);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("minishell: %s: No such file or directory\n",
				token[1]), 127);
	}
	return (0);
}

int	output_redir_append(t_cmd *cmd, char **token)
{
	close(cmd->fd[WRITE_END]);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("minishell: %s: No such file or directory\n",
				token[1]), 127);
	}
	return (0);
}

int	ft_redir_heredoc(char *heredoc, int *exit_code)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_error("Pipe Error\n", NULL), 1);
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error\n", NULL), 1);
	else if (pid == 0)
	{
		close(pipefd[READ_END]);
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
		close(pipefd[WRITE_END]);
		ft_putstr_fd(heredoc, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, exit_code, 0);
		close(pipefd[WRITE_END]);
		return (pipefd[READ_END]);
	}
}

int	input_heredoc(t_cmd *cmd, char **token)
{
	char	*input;
	char	*heredoc;
	int		extern_stdout;
	int		exit_code;

	input = NULL;
	heredoc = NULL;
	if (cmd->fd[READ_END] != -1)
	{
		close(cmd->fd[READ_END]);
	}
	extern_stdout = dup(STDOUT_FILENO);
	dup2(cmd->data->saved_stdin, STDIN_FILENO);
	dup2(cmd->data->saved_stdout, STDOUT_FILENO);
	input = readline("> $ ");
	while (input && ft_strncmp(input, token[1], ft_strlen(token[1])))
	{
		heredoc = ft_join_free(heredoc, input, 2);
		heredoc = ft_join_free(heredoc, "\n", 1);
		input = readline("> $ ");
	}
	cmd->fd[READ_END] = ft_redir_heredoc(heredoc, &exit_code);
	return (free(input), free(heredoc), dup2(extern_stdout, STDOUT_FILENO),
		close(extern_stdout), 0);
}

int	input_redir(t_cmd *cmd, char **token);
int	input_heredoc(t_cmd *cmd, char **token);
int	output_redir(t_cmd *cmd, char **token);
int	output_redir_append(t_cmd *cmd, char **token);
