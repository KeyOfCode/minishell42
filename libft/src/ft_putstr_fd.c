/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:18:44 by darismen          #+#    #+#             */
/*   Updated: 2024/03/13 18:35:01 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			write(fd, &s[i++], 1);
	return (1);
}

/* Parámetros 
	s: La string a enviar.
	fd: El file descriptor sobre el que escribir.
Valor devuelto 
	Nada
Funciones autorizadas
	write
Descripción 
	Envía la string ’s’ al file descriptor
	especificado. */