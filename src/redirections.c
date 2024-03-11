/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/09 19:59:38 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[READ_END] != -1)
		close(cmd->fd[READ_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near \
unexpected token `newline\'"), 1);
	cmd->fd[READ_END] = open(token[1], O_RDONLY);
	if (cmd->fd[READ_END] < 0)
	{
		return (ft_error("bash: infile: No such file or directory"), 127);
	}
	return (0);
}

// 	ft_printf_fd(2, "infile: %s\n", token[1]);

int	output_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[WRITE_END] != -1)
		close(cmd->fd[WRITE_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near \
unexpected token `newline\'"), 1);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("bash: outfile: No such file or directory"), 127);
	}
	return (0);
}

// ft_printf_fd(2, "outfile: %s\n", token[1]);

int	output_redir_append(t_cmd *cmd, char **token)
{
	if (cmd->fd[WRITE_END] != -1)
		close(cmd->fd[WRITE_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near \
unexpected token `newline\'"), 1);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("bash: app_outfile: No such file or directory"), 127);
	}
	return (0);
}

// 	ft_printf_fd(2, "append outfile: %s\n", token[1]);

int	ft_redir_heredoc(char *heredoc, int *exit_code)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ft_error("Pipe Error"), 1);
	pid = fork();
	if (pid < 0)
		return (ft_error("Fork Error"), 1);
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
		close(pipefd[WRITE_END]);
		dup2(pipefd[READ_END], STDIN_FILENO);
		close(pipefd[READ_END]);
		waitpid(pid, exit_code, 0);
	}
	return (WEXITSTATUS(exit_code));
}

/**
 * @brief TODO: Currently, other inputs take precedence over
 * the heredoc, even when set after. Talk to Pablo for help.
 * 
 * @param cmd 
 * @param token 
 * @return int 
 */
int	input_heredoc(t_cmd *cmd, char **token)
{
	char	*input;
	char	*heredoc;
	int		extern_stdout;
	int		exit_code;

	if (token[1] == NULL)
		return (ft_error("bash: syntax error near \
unexpected token `newline\'"), 1);
	input = NULL;
	heredoc = NULL;
	extern_stdout = dup(STDOUT_FILENO);
	dup2(cmd->data->saved_stdin, STDIN_FILENO);
	dup2(cmd->data->saved_stdout, STDOUT_FILENO);
	input = readline("> $ ");
	while (input && ft_strncmp(input, token[1], ft_strlen(token[1])))
	{
		heredoc = ft_join_free(heredoc, input);
		heredoc = ft_join_free(heredoc, "\n");
		free(input);
		input = readline("> $ ");
	}
	free(input);
	ft_redir_heredoc(heredoc, &exit_code);
	dup2(extern_stdout, STDOUT_FILENO);
	close(extern_stdout);
	return (exit_code);
}

int	input_redir(t_cmd *cmd, char **token);
int	input_heredoc(t_cmd *cmd, char **token);
int	output_redir(t_cmd *cmd, char **token);
int	output_redir_append(t_cmd *cmd, char **token);
