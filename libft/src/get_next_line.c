/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:28:52 by darismen          #+#    #+#             */
/*   Updated: 2024/03/19 14:58:59 by darismen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_memory(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

int	found_newline(char *line, int buf_size)
{
	int	i;

	i = 0;
	if (!(line))
		return (0);
	while (i++ < buf_size)
		if (line[i] == '\n')
			return (1);
	return (0);
}

int	newline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*clean_stash(char **stash)
{
	int		start;
	int		end;
	char	*line;
	char	*tmp;

	end = ft_strlen(*stash);
	if (!(end))
	{
		free_memory(stash);
		return (NULL);
	}
	start = newline(*stash);
	if (!end)
		end = start;
	line = ft_substr(*stash, 0, start);
	tmp = ft_substr(*stash, start, end - start);
	free_memory(stash);
	*stash = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*stash = NULL;
	char			*line;
	char			buf[BUFFER_SIZE + 1];
	int				check;
	int				break_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &stash, 0) < 0)
		return (free_memory(&stash));
	break_read = 0;
	while (!break_read)
	{
		check = (int)read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (free_memory(&stash));
		buf[check] = '\0';
		line = ft_strjoin(stash, buf);
		if (found_newline(buf, BUFFER_SIZE) || check < BUFFER_SIZE)
			break_read = 1;
		free_memory(&stash);
		stash = line;
	}
	return (clean_stash(&stash));
}
