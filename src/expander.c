/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2023/12/13 21:17:33 by darismen         ###   ########.fr       */
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
char	*ft_env_expand(char *str, t_env *envp, int *i)
{
	t_env	*head;
	char	*new;

	head = envp;
	if (str[0] == '~' && ft_strlen(str) == 1)
		str = "$HOME";
	while (head)
	{
		if (ft_strncmp (&str[1], head->nm, ft_strlen(head->nm)) == 0)
		{
			new = head->val;
			printf("before i: %d\n", *i);
			*i += ft_strlen(head->nm);
			printf("after i: %d\n", *i);
			return (new);
		}
		head = head->next;
	}
	return ("");
}
/* 
int	ft_count_vars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = ft_quotes(str, i, '\'');
		if ((ft_strchr("$~", str[i])))
			count++;
		i++;
	}
	return (count);
}
 */

/**
 * @brief Currently, *i doesn't work. Check with someone that 
 * knows pointers very well.
 * 
 * @param str 
 * @param env 
 * @param mode 
 * @return char* 
 */
char	*ft_subdivide(char *str, t_env *env, int mode)
{
	static int		i;
	char			*new;
	int				start;

	if (mode == 0)
		i = 0;
	start = i;
	if (ft_strchr("$~", str[i]))
	{
		new = ft_env_expand(str, env, &i);
		return (new);
	}
	else
	{
		while (!ft_strchr("$~", str[i]) && str[i] != '\0')
			i++;
		return (ft_substr(str, start, i - start));
	}
}

/**
 * @brief CONSIDER CALLING THIS FUNCTION FOR EACH "$"
 * THAT WAY I DON'T HAVE TO COUNT THE DAMN SPLITS???
 * NO BUT WHAT ABOUT IF THERE'S A STRING AFTER???
 * 
 * A: MAKE WHAT'S AFTER A SUBSTRING THEN RUN IT AGAIN IF IT HAS "$"
 * CONSIDER MAKE IT RECURSIVE BY CALLING ITSELF USING &STR[I]
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
	printf("\nstr: %s\n", str);
	while (str[++i])
	{
		if (str[i] == '\'')
			i = ft_quotes(str, i, '\'');
		if (ft_strchr("$~", str[i]))
		{
			aux = ft_substr(str, 0, i);
			printf("\naux: %s\n", aux);
			printf("str[i]: %c\n", str[i]);
			var = ft_env_expand(&str[i], data->env_lst, &i);
			printf("after str[i]: %c\n", str[i]);
			printf("var: %s\n", var);
			full = ft_strjoin(aux, var);
			i++;
			return (ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (str);
}

/*
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
*/

void	ft_expander(t_mini *data)
{
	int		i;

	i = 0;
	while (data->full_cmd[i])
	{
		printf("Current token: %s\n", data->full_cmd[i]);
		data->full_cmd[i] = ft_substr_expand(data->full_cmd[i], data);
		printf("\nTransformed token: %s\n", data->full_cmd[i]);
		i++;
	}
}
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