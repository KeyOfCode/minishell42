/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:38 by noelgarc          #+#    #+#             */
/*   Updated: 2024/03/22 13:20:45 by darismen         ###   ########.fr       */
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
	char	*aux;
	t_env	*head;
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
		ft_printf_fd(2, "1: %s\n", data->full_path[i]);
	}
	free(aux);
	return (data);
}

char	*get_cmd_path(t_mini *data, t_cmd *cmd)
{
	char	*try_path;
	int		i;

	i = -1;
	try_path = NULL;
	if (!save_path(data))
		try_path = ft_strdup(cmd->c_abs_path);
	if (try_path && access(try_path, F_OK) == 0)
		return (cmd->c_env_path = ft_strdup(try_path),
			free(try_path), cmd->c_env_path);
	if (data->full_path == NULL)
		return (NULL);
	while (data->full_path[++i])
	{
		ft_printf_fd(2, "full: %s\n", data->full_path[i]);
		ft_printf_fd(2, "try: %s\n", try_path);
		if (!ft_strncmp(cmd->c_abs_path, data->full_path[i],
				ft_strlen(data->full_path[i])))
			try_path = ft_strdup(cmd->c_abs_path);
		else
			try_path = ft_strjoin(data->full_path[i], cmd->c_abs_path);
		free(data->full_path[i]);
		ft_printf_fd(2, "3: %s\n", data->full_path[i]);
		ft_printf_fd(2, "try: %s\n", try_path);
		if (access(try_path, F_OK) == 0)
			return (cmd->c_env_path = ft_strdup(try_path),
				free(try_path), cmd->c_env_path);
		try_path = NULL;
	}
	free(try_path);
	return (NULL);
}

char	*env_join(t_env *head)
{
	char	*val_tmp;
	char	*result;

	val_tmp = ft_strjoin("=", head->val);
	result = ft_strjoin(head->nm, val_tmp);
	free(val_tmp);
	return (result);
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

		// ft_printf_fd(2, "%s", head->nm);
		// if (head->equal)
		// 	ft_printf_fd(2, "=\"%s\"", head->val);
		// ft_printf_fd(2, "\n");