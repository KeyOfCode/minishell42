/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:02:14 by darismen          #+#    #+#             */
/*   Updated: 2024/03/11 16:40:46 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# pragma region CONSTANTS

# define ILLEGAL "ILLEGAL"
# define E_O_F "EOF"
// Identifiers + literals
# define IDENT "IDENT"// add, foobar, x, y, ...
# define INT "INT" // 1343456

// Operators
# define ASSIGN "="
# define PLUS "+"
// Delimiters
# define COMMA ","
# define SEMICOLON ""
# define LPAREN "("
# define RPAREN ")"
# define LBRACE  "{"
# define RBRACE "}"
// Keywords
# define FUNCTION "FUNCTION"
# define LET "LET"
# define PATH_MAX 255
# define READ_END 0
# define WRITE_END 1

# pragma endregion

/**
 * @brief Pipes
 * @param in
 * @param out
 * @param last
 * @param out_error	
 */
typedef struct s_pipe
{
	int	fd[2][2];
	int	in;
	int	out;
	int	last;
	int	out_error;
}	t_pipe;

typedef enum s_flags
{
	IN,
	READ,
	OUT,
	APPEND,
}	t_flags;

/**
 * @brief	Command Nodes
 * 
 * 
 * @param c_args[0]		-> contains the cmd as the usu writes
 *					(WITH or WITHOUT absolute path)
 * @param c_args[...]	-> contains the arguments and flags of the command
 * @param c_abs_path	-> contains a copy of c_args[0] 
 * 						(WITH or WITHOUT abs_path)
 * @param c_env_path	-> contains a copy of c_abs_path if it has an abs_path,
 * 					OR a correct access path from $PATH
 * 					when c_args[0] don't have abs_path
 * 
 */

struct	s_mini;

//? add pointer back to t_mini??
typedef struct s_cmd
{
	char			**c_args;
	char			*c_abs_path;
	char			*c_env_path;
	int				fd[2];
	int				infile;
	int				outfile;
	t_flags			*flag;
	struct s_mini	*data;
	struct s_cmd	*next;
}	t_cmd;

/**
 * @brief t_env: linked list with all enviroment variables
 * @param nm variable's name
 * @param val variable's value
 * @param equal int = 1 has an equal sign, int = 0 does not.
 * @param next pointer to the next env
 */
typedef struct s_env
{
	char			*nm;
	char			*val;
	int				equal;
	struct s_env	*next;
}	t_env;

/**
 * @brief t_prompt: data structure for the prompt.
 * @param cmds: Una lista enlazada que almacenará comandos (estructuras t_mini).
 * @param envp: Un array que contiene las variables de entorno del shell.
 * @param pid: El identificador de proceso de la instancia actual del shell.
 */
// typedef struct s_prompt
// {
// 	t_list	*cmds;
// 	char	**envp;
// 	pid_t	pid;
// }		t_prompt;

/**
 * @brief t_mini: data structure for each command?
 * @param cmd_lst: *list of t_cmd nodes.
 * @param env_lst: *list of t_env variables.
 * @param full_cmd: Un arreglo que contiene el comando y sus argumentos.
 * @param full_path: La ruta completa del ejecutable si no es un comando 
 * interno (NULL si es un comando interno).
 * @param infile: Descriptor de archivo para la entrada del comando.
 * @param outfile: Descriptor de archivo para la salida del comando.
 */
typedef struct s_mini
{
	char	*prompt;
	t_cmd	*cmd_lst;
	int		cmd_count;
	t_env	*env_lst;
	char	**envp;
	char	**full_cmd;
	char	**full_path;
	int		saved_stdin;
	int		saved_stdout;
	int		fd[2];
}		t_mini;

/**
 * @brief t_global: Global structure that contains general data of the program.
 * @param exit_code: Exit status of the last process executed.
 * @param pid: Current process id.
 */
typedef struct	s_global
{
	int	exit_code;
	int	pid;
}	t_global;

extern t_global g_status;

/* Functions */
void	ft_error(char *err_msg);
void	ft_print_splits(char **splits);
void	ft_print_cmds(t_cmd **cmds);
char	*ft_join_free(char *s1, char *s2);
void	ft_printf_fd(int fd, char const *str, ...);

/* Lexer */
char	**ft_cmdtrim(char *s);
int		ft_quotes(char *s, size_t i, char q);

/* Expander */
void	ft_expander(t_mini *data);

void	*ft_cmdlst(t_mini *data);

/* Parser */
void	ft_parser(t_mini *data);

/* env */
t_env	*ft_2rows_split(char *str);
void	ft_dup_envp(t_mini *data, char **envp);
void	ft_add_envp(t_mini *data, char **envp);
int		ft_env_forbidden_chars(char *name, int len);
void	ft_env_lstadd_back(t_mini *data, t_env *new);
void	ft_env_add_or_replace(t_mini *data, t_env *new);
void	ft_env_remove(t_mini *data, char *str);
void	ft_env_lstclear(t_env *env);
void	set_env(t_mini *data, char *name, char *value);
char	*get_env(t_mini *data, char *name);

/* Builtins */
int		pwd(void);
int		env(t_mini *data);
int		unset(t_mini *data, t_cmd *cmd);
int		echo(t_cmd	*cmd);
int		export(t_mini *data, t_cmd *cmd);
int		cd(t_mini *data, t_cmd *cmd);
void	empty_export(t_mini *data);
void	ft_mini_exit(t_mini *data);
int		isbuiltin(t_cmd *head);

/* signals */
void	handle_sigint(int sig);

/* Executor */
int		ft_executor(t_mini *data, t_cmd *cmd);
char	*get_cmd_path(t_mini *data, t_cmd *cmd);
void	save_path(t_mini *data);
void	update_envp(t_mini *data);
char	*get_cmd_path(t_mini *data, t_cmd *cmd);
void	ft_builtin(t_mini	*data, t_cmd *head);

/* Redirections */
int		input_redir(t_cmd *cmd, char **token);
int		input_heredoc(t_cmd *cmd, char **token);
int		output_redir(t_cmd *cmd, char **token);
int		output_redir_append(t_cmd *cmd, char **token);

/* cmd */
int		isredir(char *arg);
void	redir_error(char *token);
int		count_cmdargs(char **args);
void	free_cmds(t_cmd **cmd_lst);


#endif
