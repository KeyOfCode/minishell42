/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:19:31 by darismen          #+#    #+#             */
/*   Updated: 2024/02/14 17:54:50 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_priv_strlen(const char *s)
{
	size_t	l;

	l = 0;
	if (s == NULL)
		return (0);
	while (s[l] != 0)
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		tot_len;
	int		i;
	char	*newstr;

	len1 = ft_priv_strlen(s1);
	tot_len = len1 + ft_priv_strlen(s2);
	newstr = (char *)malloc(tot_len + 1);
	if (!(newstr))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		newstr[i] = s1[i];
		i++;
	}
	i = 0;
	while (len1 + i < tot_len)
	{
		newstr[len1 + i] = s2[i];
		i++;
	}
	newstr[len1 + i] = '\0';
	return (newstr);
}
/* 
#include <stdlib.h>
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
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";
	char	*strjoin;
	int		arg;


	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 2)
	{
		s1[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 3)
	{
		s2[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	else if (arg == 4)
	{
		s1[0] = '\0';
		s2[0] = '\0';
		if (!(strjoin = ft_strjoin(s1, s2)))
			ft_print_result("NULL");
		else
			ft_print_result(strjoin);
		if (strjoin == s1 || strjoin == s2)
			ft_print_result("\nA new string was not returned");
	}
	return (0);
}
 */