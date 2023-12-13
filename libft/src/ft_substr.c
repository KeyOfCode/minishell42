/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:34:13 by darismen          #+#    #+#             */
/*   Updated: 2023/12/08 20:29:58 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

size_t	priv_substr_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

/**
 * @brief Creates a substring from a string
 * 
 * @param s 	input string
 * @param start	starting position
 * @param len 	lenght of substring
 * @return char* 
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	true_len;

	i = 0;
	true_len = priv_substr_strlen(s);
	if (start >= true_len)
	{
		subs = (char *)malloc(sizeof(char) * 1);
		subs[0] = '\0';
		return (subs);
	}
	if (true_len <= len)
		subs = (char *)malloc(sizeof(char) * (true_len + 1));
	else
		subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!(subs))
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		subs[i++] = s[start];
		start++;
	}
	subs[i] = '\0';
	return (subs);
}
/* #include <stdlib.h>
#include <unistd.h>

void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int		main(int argc, const char *argv[])
{
	char	str[] = "lorem ipsum dolor sit amet";
	char	*strsub;
	int		arg;

	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (!(strsub = ft_substr(str, 0, 10)))
			ft_print_result("NULL");
		else
			ft_print_result(strsub);
		if (str == strsub)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 2)
	{
		if (!(strsub = ft_substr(str, 7, 10)))
			ft_print_result("NULL");
		else
			ft_print_result(strsub);
		if (str == strsub)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 3)
	{
		if (!(strsub = ft_substr(str, 7, 0)))
			ft_print_result("NULL");
		else
			ft_print_result(strsub);
		if (str == strsub)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 4)
	{
		if (!(strsub = ft_substr(str, 0, 0)))
			ft_print_result("NULL");
		else
			ft_print_result(strsub);
		if (str == strsub)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 5)
	{
		char *bullshit;
		if (!(strsub = ft_substr(str, 400, 20)))
			ft_print_result("NULL");
		else
		{
			bullshit = (char *)&strsub[30];
			bullshit = "FULL BULLSHIT";
			if (strsub)
				ft_print_result(strsub);
			else
				ft_print_result("rip");
		}
		if (str == strsub)
			ft_print_result("\nA new string was not returned");
		(void)bullshit;
	}
	return (0);
}
 */
/* Reserva (con malloc(3)) y devuelve una substring de
la string ’s’.
La substring empieza desde el índice ’start’ y
tiene una longitud máxima ’len’. */