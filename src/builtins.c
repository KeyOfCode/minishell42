/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/01/24 20:06:47 by darismen         ###   ########.fr       */
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

	// char	*buffer;
	// size_t	size;
	// buffer = 0;
	// size = 0;

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

//Apparently, export puts new variables at the top??
void	export(t_mini *data, t_cmd *cmd)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	if (ft_env_forbidden_chars(cmd->c_args[1], ft_strlen(cmd->c_args[1])))
	{
		printf("export: `%s': not a valid identifier\n", cmd->c_args[1]);
		return ;
	}
	new->nm = cmd->c_args[1];
	if (cmd->c_args[2] && !ft_strncmp(cmd->c_args[2], "=", 1))
	{
		new->val = cmd->c_args[3];
		new->equal = 1;
	}
	else
	{
		new->val = NULL;
		new->equal = 0;
	}
	ft_env_lstadd_back(data, new);
}

// void	local_to_export(t_mini *data);

void	unset(t_mini *data, char *str)
{
	t_env	*head;
	t_env	*del;

	head = data->env_lst;
	if (str[0] == '~')
		str = "$HOME";
	while (head->next)
	{
		if (ft_strncmp (&str[1], head->next->nm,
				ft_strlen(head->next->nm)) == 0)
		{
			del = head->next;
			head->next = del->next;
			free(del);
			printf("unset success!\n");
			return ;
		}
		head = head->next;
	}
}
