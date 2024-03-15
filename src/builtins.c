/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/15 11:49:42 by disantam         ###   ########.fr       */
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
			printf("%s=%s\n", head->nm, head->val);
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
		printf("declare -x %s", head->nm);
		if (head->equal)
			printf("=\"%s\"", head->val);
		printf("\n");
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
