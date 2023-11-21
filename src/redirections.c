/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:04:59 by noelgarc          #+#    #+#             */
/*   Updated: 2023/11/19 09:17:17 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    casos <:
    -   sort < file.txt 
    -   sort < src/file.txt (ruta relativa)
    -   ruta absoluta (comienza por /)
    -   sort < $PWD/file.txt
*/