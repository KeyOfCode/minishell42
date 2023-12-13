/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:39:10 by darismen          #+#    #+#             */
/*   Updated: 2023/12/08 18:31:32 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define BASE_HEX "0123456789abcdef"
# define MAY_BASE_HEX "0123456789ABCDEF"
# define BASE_DEC "0123456789"
# include "libft.h"

int		ft_printf(char const *str, ...);
int		ft_putchar(int c);
int		ft_putnbr(char *base, unsigned long long n);
int		ft_putstr(char *str);
int		ft_putptr(void *ptr);
int		ft_puthex(unsigned int n, char cap);
int		ft_putunsigned(unsigned int n);
int		ft_putsigned(int n);
int		ft_num_len(unsigned long value, char *base);
// size_t	ft_strlen(const char *s);

#endif