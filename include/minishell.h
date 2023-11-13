/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:02:14 by darismen          #+#    #+#             */
/*   Updated: 2023/11/13 18:42:02 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <readline/readline.h>

//int	g_status;
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

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list; */

typedef struct s_token
{
	void	*attr;
	char	*value;
}	t_token;

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

#endif