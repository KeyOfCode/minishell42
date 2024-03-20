/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:41:05 by darismen          #+#    #+#             */
/*   Updated: 2024/03/19 18:40:03 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "printf.h"
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Check if alphabetic */
int				ft_isalpha(int c);
/* Check if digit */
int				ft_isdigit(int c);
/* Check if digit */
int				ft_islower(int c);
/* Check if digit */
int				ft_isupper(int c);
/* Check if alphanumeric */
int				ft_isalnum(int c);
/* Check if is ASCII */
int				ft_isascii(int c);
/*Check if is printable*/
int				ft_isprint(int c);
/*Return size of the string */
size_t			ft_strlen(const char *str);
/*Writes len bytes of value c (converted to 
	an unsigned char) to the string b. */
void			*ft_memset(void *b, int c, unsigned int len);
/*Writes len bytes of value to the string b. */
void			ft_bzero(void *s, unsigned long n);
/*Copies n bytes from memory area src to memory area
     dst.  If dst and src overlap, behavior is undefined.*/
void			*ft_memcpy(void *dest, const void *src, size_t size);
/* Copies len bytes from string src to string dst.  
	The two strings may overlap; */
void			*ft_memmove(void *dest, const void *src, unsigned int len);
/* Copies up to dstsize - 1 characters from the string src to dst*/
size_t			ft_strlcpy(char *dest, char *src, size_t size);
/* Locates the first occurrence of c in string s. 
	Returns a pointer to the byte located, 
	or NULL if no such byte exists within n
	bytes.*/
void			*ft_memchr(const void *s, int c, size_t n);
/* compares byte string s1 against byte string s2.  
	Both strings are assumed to be n bytes long. */
int				ft_memcmp(const void *s1, const void *s2, size_t n);
/* Appends string src to the end of dst. */
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
/* Converts a lower-case letter to the corresponding upper-case letter. */
int				ft_toupper(int str);
/* Converts an upper-case letter to the corresponding lower-case letter. */
int				ft_tolower(int str);
/* Locates the first occurrence of c (converted to a char) in the string */
char			*ft_strchr(const char *s, int c);
/* Locates the last occurrence of c (converted to a char) in the string */
char			*ft_strrchr(const char *s, int c);
/* Compares not more than n characters. */
int				ft_strncmp(char *s1, char *s2, unsigned int n);
/* Locates a substring in a string */
char			*ft_strnstr(const char *str, const char *sub, size_t len);
/* Convert ASCII string to integer */
int				ft_atoi(const char *str);
/* Contiguously allocates enough space for count objects 
	that are size bytes of memory each and returns 
	a pointer to the allocated memory.  
	The allocated memory is filled with bytes of value zero. */
void			*ft_calloc(unsigned int count, unsigned int size);
/* Allocates sufficient memory for a copy of the string s1, does the copy, and
     returns a pointer to it. */
char			*ft_strdup(const char *s1);
/* Allocates sufficient memory for a copy of the string s1, does the copy, and
     returns a pointer to it. */
char			*ft_strndup(const char *s1, size_t n);
/* ************************************************************************** */

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
void			ft_errorf(char const *s);

char			*ft_chrrmv(char *str, char c);

/* ************************************************************************** */
/* t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *)); */

#endif