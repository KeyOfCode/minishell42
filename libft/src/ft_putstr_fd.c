/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:18:44 by darismen          #+#    #+#             */
/*   Updated: 2022/10/07 17:53:37 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			write(fd, &s[i++], 1);
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