/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:02:49 by darismen          #+#    #+#             */
/*   Updated: 2024/04/02 14:05:35 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	int		i;
	int		len;

	len = 0;
	while (s1[len] != 0)
		len++;
	s2 = (char *)malloc(len + 1);
	if (!(s2))
		return (NULL);
	i = 0;
	while (s1[i] && (size_t)i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
