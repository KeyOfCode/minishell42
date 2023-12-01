/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noelgarc <noelgarc@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:59:06 by noelgarc          #+#    #+#             */
/*   Updated: 2023/12/01 17:59:09 by noelgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_store_string(char *str, size_t *pos)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = *pos;
	while (str[i] == ' ' && str[i])
		i++;
	j = i;
	if (ft_strchr("|<>", str[i]) && str[i] != '\0')
		ft_spchar(str, &i, pos, 1);
	else
	{
		while (!ft_strchr(" |<>", str[i]) && str[i] != '\0')
		{
			if (str[i] == '\"')
				i = ft_quotes(str, i, '\"');
			else if (str[i] == '\'')
				i = ft_quotes(str, i, '\'');
			i++;
		}
	}
	if (i > j)
		*pos = i;
	result = ft_strndup(&str[j], i - j);
	return (result);
}
