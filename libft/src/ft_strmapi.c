/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:02:54 by darismen          #+#    #+#             */
/*   Updated: 2022/10/15 21:57:46 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	int		i;
	int		len;

	len = 0;
	while (s[len] != 0)
		len++;
	newstr = (char *)malloc(len + 1);
	if (!(newstr))
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

/*
Parameters 
	s: The string on which to iterate.
	f: The function to apply to each character.

Return value 
	The string created from the successive applications of ’f’.
	Returns NULL if the allocation fails.

Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’. */