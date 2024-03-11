/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/09 19:43:29 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	*current;

	current = getcwd(NULL, 0);
	ft_putendl_fd(current, 1);
	free(current);
	return (0);
}

int	env(t_mini *data)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		if (head->equal)
		{
			ft_putstr_fd(head->nm, 1);
			ft_putstr_fd(head->val, 1);
			ft_putstr_fd("\n", 1);
		}
		head = head->next;
	}
	return (0);
}

void	empty_export(t_mini *data)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(head->nm, 1);
		if (head->equal)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(head->val, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		head = head->next;
	}
}

int	export(t_mini *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd->c_args[1])
		empty_export(data);
	else
		ft_add_envp(data, &cmd->c_args[1]);
	return (0);
}

int	unset(t_mini *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->c_args[++i])
		ft_env_remove(data, cmd->c_args[i]);
	return (0);
}

/* void	ft_add_envp(t_mini *data, char *envp)
{
	int		i;
	t_env	*node;

	i = -1;
	node = ft_2rows_split(envp);
	node->next = NULL;
	if (!node)
		return ;
	if (ft_env_forbidden_chars(node->nm, ft_strlen(node->nm)))
	{
		ft_putstr_fd("export: '%s': not a valid identifier\n", node->nm);
		free (node);
		return ;
	}
	ft_env_add_or_replace(data, node);
} */