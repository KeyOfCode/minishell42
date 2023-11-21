/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:15:48 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/20 21:17:02 by noelgarc         ###   ########.fr       */
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
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_node;

// get path

char    *get_full_path(char *file);

// absolute path

t_list	*create_node(char *str);
void	print_list(t_list *list);
void	free_list(t_list *list);
char	**free_splitted(char **splitted);

t_list	*matrix_to_list(char **str);
t_list	*remove_last_node(t_list **list);
t_list	*add_or_delete(t_list *list);
char	*strjoin_list(t_list *list);

char	*get_absolute_path(char *str);
t_list	*dup_list(t_list *list);








#endif