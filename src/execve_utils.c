/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/15 13:54:57 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*save_path(t_mini *data)
{
	char	*aux;
	t_env	*head;
	int		i;

	head = data->env_lst;
	while (head && ft_strncmp(head->nm, "PATH", 4))
		head = head->next;
	if (!head)
		return (NULL);
	if (!ft_strncmp(head->nm, "PATH", 4))
	{
		data->full_path = ft_split(head->val, ':');
	}
	i = -1;
	while (data->full_path[++i])
	{
		aux = ft_strjoin(data->full_path[i], "/");
		free(data->full_path[i]);
		data->full_path[i] = aux;
	}
	free(aux);
	return (data);
}

char	*get_cmd_path(t_mini *data, t_cmd *cmd)
{
	char	*try_path;
	int		i;

	i = -1;
	if(!save_path(data))
		return (NULL);
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
	return (NULL);
}

void	ft_free_matrix(char **matrix)
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
}

void	update_envp(t_mini *data)
{
	t_env	*head;
	int		i;

	head = data->env_lst;
	i = 0;
	if (data->envp)
		ft_free_matrix(data->envp);
	while (head != NULL)
	{
		head = head->next;
		i++;
	}
	data->envp = ft_calloc(i + 1, sizeof(char *));
	if (!data->envp)
		return ;
	i = -1;
	head = data->env_lst;
	while (head != NULL)
	{
		if (head->equal)
			data->envp[++i] = ft_strjoin(head->nm, ft_strjoin("=", head->val));
		else
			data->envp[++i] = ft_strdup(head->nm);
		head = head->next;
	}
}
