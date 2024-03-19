/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/18 16:15:34 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Currently doesn't considers if the env doesn't have a =
 * 
 * @param str 
 * @param envp 
 * @param i 	Pointer to the counter in ft_subdivide so I can count
 * over the env. Because it's a pointer, I don't need to return it.
 * @return char* 
 */
char	*ft_env_expand(char *ogstr, t_env *envp, int *i)
{
	t_env	*head;
	char	*new;
	char	*str;

	head = envp;
	str = ogstr;
	if (str[0] == '~')
		str = "$HOME";
	while (head)
	{
		if (ft_strncmp (&str[1], head->nm, ft_strlen(head->nm)) == 0)
		{
			new = head->val;
			if (ogstr[0] != '~')
				*i += ft_strlen(head->nm);
			return (new);
		}
		head = head->next;
	}
	if (ft_strchr("?", str[1]))
	{
		return (new = ft_itoa(g_status), *i += 1, new);
	}
	return ("");
}

/**
 * @brief 
 * 
 * @param str 
 */
char	*ft_substr_expand(char	*str, t_mini *data)
{
	char	*full;
	char	*aux;
	char	*var;
	int		i;

	i = -1;
	full = "";
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i = ft_quotes(str, i, '\'');
		}
		if (ft_strchr("$~", str[i]))
		{
			aux = ft_substr(str, 0, i);
			var = ft_env_expand(&str[i], data->env_lst, &i);
			full = ft_strjoin(aux, var);
			free(aux);
			i++;
			return (ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (str);
}

char	*ft_chrrmv(char *str, char c)
{
	char	*newstr;
	int		i;
	int		j;
	int		rm;

	i = 0;
	rm = 0;
	while (str[i])
	{
		if (str[i++] == c)
			rm++;
	}
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - rm + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			newstr[j++] = str[i];
		}
		i++;
	}
	free(str);
	return (newstr);
}

void	ft_expander(t_mini *data)
{
	int		i;

	i = 0;
	while (data->full_cmd[i])
	{
		data->full_cmd[i] = ft_substr_expand(data->full_cmd[i], data);
		if (data->full_cmd[i][0] == '"')
		{
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\"');
		}
		else if (data->full_cmd[i][0] == '\'')
		{
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\'');
		}
		i++;
	}
}
