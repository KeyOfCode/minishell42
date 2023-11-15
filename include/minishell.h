/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:02:14 by darismen          #+#    #+#             */
/*   Updated: 2023/11/15 20:41:19 by darismen         ###   ########.fr       */
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

# pragma endregion

typedef struct s_env
{
	char			*nm;
	char			*val;
	int				equal;
	struct s_env	*next;
}	t_env;

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	t_env	**env_lst;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

#endif