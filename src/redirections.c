/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/18 16:26:01 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[READ_END] != cmd->data->saved_stdin)
	{
		close(cmd->fd[READ_END]);
	}
	ft_error("infile: %s\n", token[1]);
	cmd->fd[READ_END] = open(token[1], O_RDONLY);
	if (cmd->fd[READ_END] < 0)
	{
		return (ft_error("minishell: %s: No such file \
or directory\n", token[1]), 127);
	}
	return (0);
}

int	output_redir(t_cmd *cmd, char **token)
{
	if (cmd->fd[WRITE_END] != cmd->data->saved_stdout)
	{
		close(cmd->fd[WRITE_END]);
	}
	ft_error("outfile: %s\n", token[1]);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("minishell: %s: No such \
file or directory\n", token[1]), 127);
	}
	return (0);
}

int	output_redir_append(t_cmd *cmd, char **token)
{
	close(cmd->fd[WRITE_END]);
	ft_error("outfile: %s\n", token[1]);
	cmd->fd[WRITE_END] = open(token[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (cmd->fd[WRITE_END] < 0)
	{
		return (ft_error("minishell: %s: No such \
file or directory\n", token[1]), 127);
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
		heredoc = ft_join_free(heredoc, input);
		heredoc = ft_join_free(heredoc, "\n");
		free(input);
		input = readline("> $ ");
	}
	free(input);
	cmd->fd[READ_END] = ft_redir_heredoc(heredoc, &exit_code);
	dup2(extern_stdout, STDOUT_FILENO);
	close(extern_stdout);
	return (0);
}

/* char	*heredoc(char *eof)
{
	char	*aux;
	char	*temp;
	char	*str;

	str = NULL;
	temp = NULL;
	while (ft_strncmp(str, eof, ft_strlen(eof)))
	{
		str = readline("> $ ");
		aux = ft_strjoin(temp, str);
		temp = aux;
	}
}

int	input_heredoc(t_cmd *cmd, char **token)
{
	char	*fd_path;
	char	*aux;
	char	*temp;
	char	*str;
	int		fd;

	(void)cmd;
	(void)token;
	str = NULL;
	temp = NULL;
	close(cmd->fd[READ_END]);
	if (token[1] == NULL)
		return (ft_error("bash: syntax error near \
unexpected token `newline\'"), 1);
	while (ft_strncmp(temp, token[1], ft_strlen(token)))
	{
		str = readline("> $ ");
		aux = ft_strjoin(temp, str);
		temp = aux;
	}
	close(cmd->fd[READ_END]);
	dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
	close(cmd->fd[WRITE_END]);
	ft_putstr_fd(temp, STDOUT_FILENO);
	return (0);
} */

int	input_redir(t_cmd *cmd, char **token);
int	input_heredoc(t_cmd *cmd, char **token);
int	output_redir(t_cmd *cmd, char **token);
int	output_redir_append(t_cmd *cmd, char **token);
