/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:19:18 by darismen          #+#    #+#             */
/*   Updated: 2022/09/22 11:23:57 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	h;
	size_t	n;
	char	t_hay;
	char	t_ned;

	h = 0;
	if (sub[0] == '\0')
		return ((char *)str);
	while (str[h] != '\0')
	{
		n = 0;
		t_hay = str[h];
		t_ned = sub[n];
		while (str[h + n] == sub[n] && (h + n) < len)
		{
			t_ned = sub[n];
			if (str[h + n] == '\0' && sub[n] == '\0')
				return ((char *)&str[h]);
			n++;
		}
		if (sub[n] == '\0')
			return ((char *)&str[h]);
		h++;
	}
	return (0);
}
