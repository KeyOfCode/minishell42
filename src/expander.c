/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/01/28 20:07:06 by darismen         ###   ########.fr       */
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
	return ("");
}

	// printf("\nstr: %s\n", str);
	// printf("before i: %d\n", *i);
	// printf("after i: %d\n", *i);

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
			i = ft_quotes(str, i, '\'');
		if (ft_strchr("$~", str[i]))
		{
			aux = ft_substr(str, 0, i);
			var = ft_env_expand(&str[i], data->env_lst, &i);
			full = ft_strjoin(aux, var);
			i++;
			return (ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (str);
}

// printf("\nstr: %s\n", str);
	// printf("\naux: %s\n", aux);
	// printf("str[i]: %c\n", str[i]);
	// printf("after str[i]: %c\n", str[i]);
	// printf("var: %s\n", var);
/*
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
*/

char	*ft_chrrmv(char *str, char c)
{
	char	*newstr;
	int		i;
	int		j;
	int		rm;

	i = 0;
	rm = 0;
	while (str[i])
		if (str[i++] == c)
			rm++;
	i = 0;
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - rm + 1));
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			newstr[j++] = str[i];
		i++;
	}
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
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\"');
		i++;
	}
}

// printf("Current token: %s\n", data->full_cmd[i]);
// printf("\nTransformed token: %s\n", data->full_cmd[i]);

/* 
void	ft_expander(t_mini *data)
{
	char	**expanded;
	int		count;
	int		i;
	int		j;

	i = 0;
	while (data->full_cmd[i])
	{
		j = 0;
		printf("Current token: %s\n", data->full_cmd[i]);
		count = ft_count_vars(data->full_cmd[i]);
		printf("nº slices: %d\n", count);
		expanded = (char **)malloc(sizeof(char *) * (count + 1));
		expanded[count] = NULL;
		while (j < count)
		{
			expanded[j] = ft_subdivide(data->full_cmd[i], data->env_lst, j);
			j++;
		}
		ft_print_splits(expanded);
		i++;
	}
}
 */
/* j = 0;
		while (data->full_cmd[i][j])
		{
			if (data->full_cmd[i][j] == '\'')
				while (data->full_cmd[i][j] != '\'')
					j++;
			if (ft_strchr("$~", data->full_cmd[i][j]))
			{
				ft_env_expand(&data->full_cmd[i][j], data->env_lst);
			}
			j++;
		} */

/**
 * @brief 
 * 
 * @param str 
 * @param env 
 * @param mode 
 * @return char* 
 */
// char	*ft_subdivide(char *str, t_env *env, int mode)
// {
// 	static int		i;
// 	char			*new;
// 	int				start;
//
// 	if (mode == 0)
// 		i = 0;
// 	start = i;
// 	if (ft_strchr("$~", str[i]))
// 	{
// 		new = ft_env_expand(str, env, &i);
// 		return (new);
// 	}
// 	else
// 	{
// 		while (!ft_strchr("$~", str[i]) && str[i] != '\0')
// 			i++;
// 		return (ft_substr(str, start, i - start));
// 	}
// }