/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:02:14 by darismen          #+#    #+#             */
/*   Updated: 2024/01/24 19:58:30 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

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
 * @param pipes			->Pointer to t_pipe
 * @param flag			->t_flags Enum (IN, READ, OUT, APPEND)
 *
 */

//? add pointer back to t_mini??
typedef struct s_cmd
{
	char			**c_args;
	char			*c_abs_path;
	char			*c_env_path;
	// pid_t			pid;
	// int				infile;
	// int				outfile;
	// int				num_args;
	t_pipe			*pipes;
	t_flags			*flag;
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
typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

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
	t_cmd	**cmd_lst;
	int		cmd_count;
	t_env	*env_lst;
	char	**envp;
	char	**full_cmd;
	char	*full_path;
	// int		infile;
	// int		outfile;
}		t_mini;

/* Functions */

void	ft_error(char *err_msg);
void	ft_print_splits(char **splits);
void	ft_dup_envp(t_mini *data, char **envp);
int		ft_env_forbidden_chars(char *name, int len);
void	ft_env_lstadd_back(t_mini *data, t_env *new);

/* Lexer */

char	**ft_cmdtrim(char *s);
int		ft_quotes(char *s, size_t i, char q);

/* Expander */
void	ft_expander(t_mini *data);

void	ft_cmdlst(t_mini *data);

/* Parser */
void	ft_parser(t_mini *data);

/* Builtins */
void	pwd(void);
void	empty_export(t_mini *data);
void	export(t_mini *data, t_cmd *cmd);
void	env(t_mini *data);
void	unset(t_mini *data, char *str);

#endif