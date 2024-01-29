/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/01/29 16:56:52 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(void)
{
	char	*current;

	current = getcwd(NULL, 0);
	ft_putendl_fd(current, 1);
	free(current);
}

void	env(t_mini *data)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		if (head->equal)
		{
			printf("%s", head->nm);
			printf("=%s", head->val);
			printf("\n");
		}
		head = head->next;
	}
}

void	empty_export(t_mini *data)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		printf("declare -x %s", head->nm);
		if (head->equal)
			printf("=\"%s\"", head->val);
		printf("\n");
		head = head->next;
	}
}

void	export(t_mini *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd->c_args[1])
		empty_export(data);
	else
		ft_add_envp(data, &cmd->c_args[1]);
}

void	unset(t_mini *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->c_args[++i])
		ft_env_remove(data, cmd->c_args[i]);
}

/* void	empty_export(t_mini *data)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		printf("declare -x %s", head->nm);
		if (head->equal)
			printf("=\"%s\"", head->val);
		printf("\n");
		head = head->next;
	}
} */

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
		printf("export: '%s': not a valid identifier\n", node->nm);
		free (node);
		return ;
	}
	ft_env_add_or_replace(data, node);
} */