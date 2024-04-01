/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/29 17:28:49 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	isdir(const char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

void	*save_path(t_mini *data)
{
	t_env	*head;
	char	*aux;
	int		i;

	head = data->env_lst;
	while (head && ft_strncmp(head->nm, "PATH", 4))
		head = head->next;
	if (!head)
		return (NULL);
	if (!ft_strncmp(head->nm, "PATH", 4) && head->val)
		data->full_path = ft_split(head->val, ':');
	i = -1;
	while (data->full_path[++i])
	{
		aux = ft_strjoin(data->full_path[i], "/");
		free(data->full_path[i]);
		data->full_path[i] = aux;
	}
	return (data);
}

char	*get_cmd_path(t_mini *data, t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!save_path(data))
		cmd->c_env_path = ft_strdup(cmd->c_abs_path);
	if (cmd->c_env_path && access(cmd->c_env_path, F_OK) == 0)
		return (cmd->c_env_path);
	if (data->full_path == NULL)
		return (NULL);
	i = -1;
	while (data->full_path[++i])
	{
		if (!ft_strncmp(cmd->c_abs_path, data->full_path[i],
				ft_strlen(data->full_path[i])))
			cmd->c_env_path = ft_strdup(cmd->c_abs_path);
		else
			cmd->c_env_path = ft_strjoin(data->full_path[i], cmd->c_abs_path);
		if (access(cmd->c_env_path, F_OK) == 0)
			return (cmd->c_env_path);
		free(cmd->c_env_path);
	}
	return (NULL);
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
			data->envp[++i] = env_join(head);
		else
			data->envp[++i] = ft_strdup(head->nm);
		head = head->next;
	}
}
