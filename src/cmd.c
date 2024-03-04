/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/04 13:30:23 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->c_args = NULL;
	cmd->c_abs_path = NULL;
	cmd->c_env_path = NULL;
	cmd->fd[WRITE_END] = STDOUT_FILENO;
	cmd->fd[READ_END] = STDIN_FILENO;
	cmd->flag = NULL;
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
	char	*token;
	int		status;

	token = *arg;
	ft_putstr_fd("token: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\n", 2);
	if (!ft_strncmp(token, "<", 1))
		status = input_redir(cmd, arg);
	if (!ft_strncmp(token, ">", 1))
		status = output_redir(cmd, arg);
	if (!ft_strncmp(token, "<<", 2))
		status = input_heredoc(cmd, arg);
	if (!ft_strncmp(token, ">>", 2))
		status = output_redir_append(cmd, arg);
	if (status > 0)
	{
		g_status = status;
		return (status);
	}
	return (status);
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
	int		count;

	count = count_cmdargs(args);
	if (count == 0)
		return (NULL);
	newcmd->c_args = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	j = 0;
	while ((j < count) || (args[i] != NULL && ft_strncmp(args[i], "|", 1)))
	{
		if (!isredir(args[i]))
			newcmd->c_args[j++] = args[i];
		else
		{
			if (check_redirections(newcmd, args + i) > 0)
				return (NULL);
			if (args[i + 1] != NULL)
				i++;
		}
		i++;
	}
	newcmd->c_abs_path = newcmd->c_args[0];
	*index += i + 1;
	return (index);
}

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

/* {current = current->next; printf("current: %s\n", current->c_abs_path);} */

/* void	ft_print_node(t_cmd **cmd_lst)
{
	t_cmd	*cmd;
	int		j;

	cmd = *cmd_lst;
	printf("node \n");
	printf("\tc_args: \n");
	j = 0;
	while (cmd->c_args[j])
		printf("\t\t%s\n", cmd->c_args[j++]);
	printf("\n\tc_abs_path: %s\n", cmd->c_args[0]);
} */

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
		return (ft_error("bash: syntax error near unexpected token `|'"), NULL);
	data->cmd_count = count;
	i = 0;
	head = 0;
	while (head < count)
	{
		newcmd = ft_init_cmd();
		if (!ft_fillcmd(newcmd, &data->full_cmd[i], &i))
			return (NULL);
		ft_cmd_lstadd_back(&data->cmd_lst, newcmd);
		head++;
	}
	ft_print_cmds(&data->cmd_lst);
	return(data);
}
/* 	printf("\nNode number %d\n\n", head);
	printf("\nft_fillcmd check! i = %d\n\n", i);
	printf("c_abs_args: %s\n\n", data->cmd_lst->c_abs_path);
	printf("Node added\n");
	printf("EXIT!\n"); 
*/

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

/* void	ft_print_node(t_mini *data)
{
	t_cmd	*cmd;
	int		j;

	cmd = *data->cmd_lst;
	printf("node \n");
	printf("\tc_args: \n");
	j = 0;
	while (cmd->c_args[j])
		printf("\t\t%s\n", cmd->c_args[j++]);
	printf("\n\tc_abs_path: %s\n", cmd->c_args[0]);
} */
