/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/12 16:17:34 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_split(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_split(allpath);
	ft_free_split(s_cmd);
	return (cmd);
} */

void	save_path(t_mini *data)
{
	char	*aux;
	t_env	*head;
	int		i;

	head = data->env_lst;
	while (head && ft_strncmp(head->nm, "PATH", 4))
		head = head->next;
	if (!ft_strncmp(head->nm, "PATH", 4))
		data->full_path = ft_split(head->val, ':');
	else
		return ;
	i = 0;
	while (data->full_path[i])
	{
		aux = ft_strjoin(data->full_path[i], "/");
		data->full_path[i] = aux;
		i++;
	}
	free(aux);
}

char	*get_cmd_path(t_mini *data, t_cmd *cmd)
{
	char	*try_path;
	int		i;

	i = -1;
	save_path(data);
	while (data->full_path[++i])
	{
		if (!ft_strncmp(cmd->c_abs_path, data->full_path[i],
				ft_strlen(data->full_path[i])))
			try_path = ft_strdup(cmd->c_abs_path);
		else
			try_path = ft_strjoin(data->full_path[i], cmd->c_args[0]);
		if (access(try_path, F_OK) == 0)
		{
			cmd->c_env_path = ft_strdup(try_path);
			free(try_path);
			return (cmd->c_env_path);
		}
	}
	free(try_path);
	return (0);
}
// printf("%s--\n", try_path);
// printf("Success: %s\n", cmd->c_env_path);
// printf("Failure: \n");
// | X_OK

/* Right now it causes error on command not found */
void	update_envp(t_mini *data)
{
	t_env	*head;
	int		i;

	head = data->env_lst;
	i = 0;
	// if (data->envp)
	// 	ft_free_matrix(data->envp);
	while (head)
	{
		head = head->next;
		i++;
	}
	data->envp = ft_calloc(i, sizeof(char *));
	if (!data->envp)
		return ;
	i = -1;
	head = data->env_lst;
	while (data->envp[++i])
	{
		if (head->equal)
			data->envp[i] = ft_strjoin(head->nm, ft_strjoin("=", head->val));
		else
			data->envp[i] = ft_strdup(head->nm);
		head = head->next;
	}
}

/* char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	return (NULL);
} */

/* char	**ft_2rows_split(char *str, char c)
{
	size_t	i;
	int		len;
	char	**matrix;

	i = -1;
	len = ft_strlen(str);
	matrix = ft_calloc(3, sizeof(char *));
	if (!str || len == 0)
		return (NULL);
	if (!matrix)
		return (NULL);
	while (str[++i] && str[i] != '=')
		;
	matrix[0] = ft_substr(str, 0, i);
	if (!matrix[0])
		return (free(matrix), NULL);
	if (str[i] == '=' && i < len - 1)
	{
		matrix[1] = ft_substr(str, i + 1, len - i - 1);
		if (!matrix[1])
			return (free(matrix), NULL);
	}
	else if (str[i] != '=' || (str[i] == '=' && i == len - 1))
		matrix[1] = ft_calloc(1, sizeof(char));
	return (matrix);
} */


/* char	**env_lst(t_mini *data, char**matrix, int mode)
{
	int		i;
	t_env	node;
	char	**env;

	i = -1;
	env = data->envp;
	if (mode == 1)
	{
	}
	// node = ft_calloc(3, sizeof(t_env));
	while (env[++i] && env[i] != '=')
		;
	node.nm = ft_substr(env, 0, i);
	if (!node.nm)
		exit(EXIT_FAILURE);
	if (env[i] == c && i < ft_strlen(env))
} */
