/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:06:09 by darismen          #+#    #+#             */
/*   Updated: 2024/03/19 14:49:46 by darismen         ###   ########.fr       */
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
	int		i;
	char	*aux;

	i = -1;
	if (str[0] == '~' && ft_strlen(str) == 1)
		return (str = ft_env_expand(str, data->env_lst, &i), str);
	while (str[++i] && g_status != 1)
	{
		if (str[i] == '\"')
			data->dquote = (data->dquote + 1) % 2;
		if (str[i] == '\'' && data->dquote == 0)
			i = ft_quotes(str, i, '\'');
		if (ft_strchr("$", str[i]))
		{
			aux = ft_substr(str, 0, i);
			full = ft_join_free(aux, ft_env_expand(&str[i], data->env_lst, &i));
			free(aux);
			return (i++, ft_strjoin(full, ft_substr_expand(&str[i], data)));
		}
	}
	return (data->dquote = 0, str);
}

		// ft_printf_fd(2, "%d ", data->dquote);
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

int	ft_flag(char str, t_mini *data, int *rm_dq, int *rm_sq)
{
	if (str == '\"' && data->squote == 0)
	{
		data->dquote = (data->dquote + 1) % 2;
		(*rm_dq)++;
		return (0);
	}
	if (str == '\'' && data->dquote == 0)
	{
		data->squote = (data->squote + 1) % 2;
		(*rm_sq)++;
		return (0);
	}
	else
		return (1);
}

		// ft_printf_fd(2, "dq_: %d \n", *rm_dq);
		// ft_printf_fd(2, "sq_: %d \n", *rm_sq);

char	*ft_quotes_rmv(t_mini *data, char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		rm_dq;
	int		rm_sq;

	i = 0;
	rm_dq = 0;
	rm_sq = 0;
	while (str[i])
		ft_flag(str[i++], data, &rm_dq, &rm_sq);
	newstr = ft_calloc((ft_strlen(str) - rm_dq - rm_sq + 1), sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_flag(str[i], data, &rm_dq, &rm_sq))
			newstr[j++] = str[i];
		i++;
	}
	free(str);
	return (data->dquote = 0, data->squote = 0, newstr);
}

/* 		ft_printf_fd(2, "%c %d %d %d %d\n", str[i],
			data->dquote, data->squote, rm_dq, rm_sq); */
		// ft_printf_fd(2, "%d ", data->dquote);
		// ft_printf_fd(2, "%d ", rm_dq);
		// ft_printf_fd(2, "%d \n", rm_sq);

void	ft_expander(t_mini *data)
{
	int		i;

	i = 0;
	while (data->full_cmd[i])
	{
		data->full_cmd[i] = ft_strdup(
				ft_substr_expand(data->full_cmd[i], data));
		data->full_cmd[i] = ft_quotes_rmv(data,
				data->full_cmd[i]);
		i++;
	}
}

/* int	ft_section(char str, t_mini *data)
{
	if (str == '\"' && data->squote == 0)
		return (0);
	else if (str == '\'' && data->dquote == 0)
		return (0);
	else
		return (1);
} */

/* 		if (data->full_cmd[i][0] == '"')
			data->full_cmd[i] = ft_chrrmv(data->full_cmd[i], '\"');
		}
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

/* char	*ft_expand_var(char *str, t_mini *data, int *i)
{
	char	*full;
	char	*aux;
	char	*var;

	aux = ft_substr(str, 0, *i);
	var = ft_env_expand(&str[*i], data->env_lst, i);
	full = ft_strjoin(aux, var);
	free(aux);
	return (full);
} */

/* char	*ft_quotes_rmv(t_mini *data, char *str, char c, char excp)
{
	char	*newstr;
	int		i;
	int		rm;

	i = 0;
	rm = 0;
	while (str[i])
	{
		ft_printf_fd(2, "%d ", data->dquote);
		ft_printf_fd(2, "%c\n", str[i]);
		if (str[i] == excp)
			data->dquote = (data->dquote + 1) % 2;
		if (str[i] == c && data->dquote == 0)
			rm++;
		i++;
	}
	newstr = ft_calloc((ft_strlen(str) - rm + 1), sizeof(char));
	i = 0;
	rm = 0;
	while (str[i])
	{
		if (str[i] != c && data->dquote == 0)
			newstr[rm++] = str[i];
		i++;
	}
	free(str);
	return (data->dquote = 0, newstr);
} */