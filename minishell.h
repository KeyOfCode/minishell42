/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:15:48 by noelgarc          #+#    #+#             */
/*   Updated: 2024/01/03 16:59:42 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <limits.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_prompt
{
	t_child	*childs;
	char	**env;
}		t_prompt;

typedef struct s_child
{
	t_list	*cmd_table;
	char	*full_path;
	int		infile;
	int		outfile;
	char	**env;

	int		child_num;
	int		heredoc;
	int		pipe[2];
	pid_t	pid;
	int		status;
	t_child	*next;
}		t_child;

/* list_utils */
void	free_list(t_list *list);
t_list	*create_node(char *str);
void	print_list(t_list *list);
t_list	*dup_list(t_list *list);
t_list	*matrix_to_list(char **str);

/* matrix_utils */
char	**free_matrix(char **matrix);

/* get_path */
char	*get_full_path(char *file);

/* absolute_path */
t_list	*remove_last_node(t_list **list);
t_list	*add_or_delete(t_list *list);
char	*strjoin_list(t_list *list);
char	*get_absolute_path(char *str);

/* parser */
void	add_to_cmd_table(char *str, t_child *childs);
void	check_token(char *str, t_child *childs,char **tokens);

/* t_child_node */
void	init_child_node(t_child *child);
void	add_child_back(t_child **head, t_child *to_add);
void	new_child_node(t_child *childs);
t_child	*get_last_child(t_child *head);

/* redirections */
void	input_redir(t_child *childs, char **tokens);
void	output_redir(t_child *childs, char **tokens);
void	output_redir_append(t_child *childs, char **tokens);

#endif