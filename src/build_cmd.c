/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/13 16:55:31 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_init_cmd(t_mini *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->c_args = NULL;
	cmd->c_abs_path = NULL;
	cmd->c_env_path = NULL;
	cmd->fd[READ_END] = -1;
	cmd->fd[WRITE_END] = -1;
	cmd->flag = NULL;
	cmd->data = data;
	cmd->next = NULL;
	return (cmd);
}

/**
 * ? Redirections. 
 * 
 *  - infile: Only accepts the last one as input, ignores all before.
 *  - heredoc: Only accepts the last one as EOF
 *  - outfile: Uses the last one as outputs, but creates all the posible 
 * outputs if they don't exist 
 *  - append: Same as output, appends the contents to the last file.
 * 
 */
int	check_redirections(t_cmd *cmd, char	**arg)
{
	int	redir_st;

	redir_st = 0;
	ft_error("token: %s\n", *arg);
	if (arg[1] == NULL)
		return (ft_error("minishell: syntax error near \
unexpected token `newline'\n", NULL), 1);
	if (isredir(arg[1]) || !ft_strncmp(arg[1], "|", 1))
	{
		return (ft_error("minishell: syntax error near \
unexpected token `%s'\n", arg[1]), 1);
	}
	if (!ft_strncmp(*arg, "<", 1))
		redir_st = input_redir(cmd, arg);
	else if (!ft_strncmp(*arg, ">", 1))
		redir_st = output_redir(cmd, arg);
	else if (!ft_strncmp(*arg, "<<", 2))
		redir_st = input_heredoc(cmd, arg);
	else if (!ft_strncmp(*arg, ">>", 2))
		redir_st = output_redir_append(cmd, arg);
	if (redir_st > 0)
		g_status = redir_st;
	return (redir_st);
}

/**
 * @brief 
 * 
 * @param newcmd 
 * @param args 
 * @return int 
 */
int	*ft_fillcmd(t_cmd *newcmd, char **args, int *index)
{
	int		i;
	int		j;
	int		c;

	c = count_cmdargs(args);
	newcmd->c_args = ft_calloc(c + 1, sizeof(char *));
	if (c == 0 || !newcmd->c_args)
		return (NULL);
	i = 0;
	j = 0;
	while ((j < c) || (args[i] != NULL && ft_strncmp(args[i], "|", 1)))
	{
		if (!isredir(args[i]))
			newcmd->c_args[j++] = args[i];
		else
		{
			if (check_redirections(newcmd, args + i) > 0)
				return (free(newcmd), NULL);
			if (args[i + 1] != NULL)
				i++;
		}
		i++;
	}
	*index += i + 1;
	return (index);
}
	// newcmd->c_abs_path = newcmd->c_args[0];

void	ft_cmd_lstadd_back(t_cmd **cmd_lst, t_cmd *new)
{
	t_cmd	*last_elem;
	t_cmd	*current;

	if (!*cmd_lst)
	{
		*cmd_lst = new;
		return ;
	}
	current = *cmd_lst;
	while (current->next)
		current = current->next;
	last_elem = current;
	last_elem->next = new;
}

void	*ft_cmdlst(t_mini *data)
{
	t_cmd	*newcmd;
	int		count;
	int		head;
	int		i;

	i = 0;
	count = 1;
	while (data->full_cmd[i])
		if (!ft_strncmp(data->full_cmd[i++], "|", 1))
			count++;
	if (data->full_cmd[0][0] == '|' || data->full_cmd[i - 1][0] == '|')
		return (ft_error("minishell: syntax error near unexpected token `%s'\n", "|"), NULL);
	data->cmd_count = count;
	i = 0;
	head = 0;
	while (head < count)
	{
		newcmd = ft_init_cmd(data);
		if (!ft_fillcmd(newcmd, &data->full_cmd[i], &i))
			return (NULL);
		newcmd->c_abs_path = newcmd->c_args[0];
		ft_cmd_lstadd_back(&data->cmd_lst, newcmd);
		head++;
	}
	return (data);
}

/* t_cmd	*ft_fillcmd(char *args, int *i)
{
	t_cmd	*newcmd;
	int		j;
	int		size;

	size = 0;
	while (args[size] && ft_strncmp(args, "|", 1))
		size++;
	j = 0;
	newcmd = ft_calloc(sizeof(t_cmd), 1);
	newcmd->c_args = ft_calloc(sizeof(char *), size);
	if (!newcmd)
		return (NULL);
	printf("num of args: %d\n", size);
	while (args[*i] && ft_strncmp(args[*i], "|", 1))
	{
		newcmd->c_args[j] = args[*i];
		printf("newcmd->c_args[%d]: %s\n", j, newcmd->c_args[j]);
		*i += 1;
		j++;
	}
	newcmd->c_abs_path = &newcmd->c_abs_path[0];
	return (newcmd);
} */

/* void	redir(t_cmd *cmd, char **tokens, int arg)
{
	int		fd;
	char	*fd_path;
	t_cmd	*last_node;

	if (!cmd|| !tokens)
		return ;
	fd_path = ft_strdup(tokens++);// obtener la nueva ruta para el fd: tokens++
	if (!fd_path)
		return ;
	if (arg == 0)
		fd = open(fd_path, O_RDONLY);
	else if (arg == 1)
		fd = open(fd_path, O_WRONLY | O_CREAT, 0644);
	else if (arg == 2)
		fd = open(fd_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(fd_path);
	if (fd < 0)
		return ;
	last_node = get_last_child(cmd);
	if (arg == 0)
		last_node->infile = fd;
	else
		last_node->outfile = fd;
} */

/* void	check_node(char *str, t_cmd *cmd, char **tokens)
{
	if (str == NULL || *str != '\0')
		return ;
	if (ft_strncmp(str, "|", 1) && ft_strlen(str) == 1)
	{
		//new_child_node(cmd);
	}
	else if (ft_strncmp(str, ">", 1) && ft_strlen(str) == 1)
		redir(cmd, tokens, 0);
	else if (ft_strncmp(str, ">>", 2) && ft_strlen(str) == 2)
		redir(cmd, tokens, 1);
	else if (ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		redir(cmd, tokens, 2);
	else if (ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
	{
		//	hereDoc
	}
	else
	{
		//	agregar a lista de argumentos full_cmd:
	}
} */

