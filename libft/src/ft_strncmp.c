/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:48:02 by darismen          #+#    #+#             */
/*   Updated: 2023/12/06 20:33:51 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief The strncmp() function compares not more than n characters.
	 Because strncmp() is designed for comparing
	 strings rather than binary data, characters that
	 appear after a `\0' character are not compared.
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return return an integer greater than, 
	 equal to, or less than 0, according
	 as the string s1 is greater than, equal to, or less
	 than the string s2.  The comparison is done using
	 unsigned characters
 */
int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (0);
}
