/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:39:10 by darismen          #+#    #+#             */
/*   Updated: 2024/03/15 14:38:17 by darismen         ###   ########.fr       */
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

int		ft_printf_fd(int fd, char const *str, ...);
int		ft_printf(char const *str, va_list args);
int		ft_putchar(int c);
int		ft_putnbr_base_fd(char *base, unsigned long long n, int fd);
int		ft_putstr(char *str);
int		ft_putptr_fd(void *ptr, int fd);
int		ft_puthex_fd(unsigned int n, char cap, int fd);
int		ft_putsigned_fd(int n, int fd);
int		ft_num_len(unsigned long value, char *base);
// int		ft_putunsigned_fd(unsigned int n, int fd);
// size_t	ft_strlen(const char *s);

#endif