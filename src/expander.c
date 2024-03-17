/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/17 20:50:12 by darismen         ###   ########.fr       */
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

char	*ft_expand_var(char *str, t_mini *data, int *i)
{
	char	*full;
	char	*aux;
	char	*var;

	aux = ft_substr(str, 0, *i);
	var = ft_env_expand(&str[*i], data->env_lst, i);
	full = ft_strjoin(aux, var);
	free(aux);
	return (full);
}

/**
 * @brief 
 * 
 * @param str 
 */
char	*ft_substr_expand(char	*str, t_mini *data)
{
	char	*full;
	int		i;
	char	*aux;

	i = -1;
	if (str[0] == '~' && ft_strlen(str) == 1)
		return (str = ft_env_expand(str, data->env_lst, &i), str);
	while (str[++i] && g_status != 1)
	{
		if (str[i] == '\"')
			data->quote = (data->quote + 1) % 2;
		if (str[i] == '\'' && data->quote == 0)
			i = ft_quotes(str, i, '\'');
		if (ft_strchr("$", str[i]))
		{
			aux = ft_substr(str, 0, i);
			full = ft_join_free(aux, ft_env_expand(&str[i], data->env_lst, &i));
			free(aux);
			ft_printf_fd(2, "variable expanded\n");
			return (i++, ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (data->quote = 0, str);
}

		// ft_printf_fd(2, "%d ", data->quote);
		// ft_printf_fd(2, "%c\n", str[i]);
		// ft_printf_fd(2, "ft_quote: %c\n", str[i]);

/* char	*ft_substr_expand(char	*str, t_mini *data)
{
	char	*full;
	int		i;
	char	*aux;
	char	*var;
	int		flag;

	i = -1;
	full = "";
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && flag == 0)
			i = ft_quotes(str, i, '\'');
		if (str[i] == '\"')
			flag = (flag + 1) % 2;
		ft_printf_fd(2, "%d\n", flag);
		if (ft_strchr("$~", str[i]))
		{
			// full = ft_expand_var(&str[i], data, &i);
			aux = ft_substr(str, 0, i);
			var = ft_env_expand(&str[i], data->env_lst, &i);
			full = ft_strjoin(aux, var);
			return (i++,
				ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (str);
} */

char	*ft_quote_rmv(t_mini *data, char *str, char c, char excp)
{
	char	*newstr;
	int		i;
	int		rm;

	i = 0;
	rm = 0;
	while (str[i])
	{
		if (str[i] == excp)
			data->quote = (data->quote + 1) % 2;
		if (str[i++] == c && data->quote == 0)
			rm++;
	}
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - rm));
	i = 0;
	rm = 0;
	while (str[i])
	{
		if (str[i] != c && data->quote == 0)
			newstr[rm++] = str[i];
		i++;
	}
	free(str);
	return (data->quote = 0, newstr);
}

void	ft_expander(t_mini *data)
{
	int		i;

	i = 0;
	while (data->full_cmd[i])
	{
		data->full_cmd[i] = ft_strdup(
				ft_substr_expand(data->full_cmd[i], data));
		if (ft_strchr(data->full_cmd[i], '\"'))
			data->full_cmd[i] = ft_quote_rmv(data, data->full_cmd[i],
					'\"', '\'');
		if (ft_strchr(data->full_cmd[i], '\''))
			data->full_cmd[i] = ft_quote_rmv(data, data->full_cmd[i],
					'\'', '\"');
		i++;
	}
}

/* 		if (data->full_cmd[i][0] == '"')
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\"');
		else if (data->full_cmd[i][0] == '\'')
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\''); */

/* int	ft_flag(char quote, int *flag)
{
	int	check;

	check = *flag;
	if (check == 0 && quote == '\"')
		check = 1;
	else if (check == 1 && quote == '\"')
		check = 0;
	ft_printf_fd(2, "%d ", check);
	return (check);
} */

// dd if=/dev/zero of=trash.txt  bs=1m  count=24
// fallocate -l 2K test.txt
