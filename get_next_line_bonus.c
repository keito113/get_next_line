/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:14:24 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/24 16:15:49 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_read_loop(int fd, char *store, char *buf)
{
	ssize_t	i;

	i = 1;
	while (i > 0 && gnl_newline_index(store) < 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		if (i == 0)
			break ;
		buf[i] = '\0';
		store = gnl_strjoin_free(store, buf);
		if (!store)
			return (NULL);
	}
	return (store);
}

static char	*read_or_free(int fd, char *store)
{
	char	*res;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		free(store);
		return (NULL);
	}
	res = gnl_read_loop(fd, store, buf);
	free(buf);
	if (!res)
	{
		free(store);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (store[fd])
		{
			free(store[fd]);
			store[fd] = NULL;
		}
		return (NULL);
	}
	store[fd] = read_or_free(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = gnl_clip_line(store[fd]);
	if (!line)
	{
		free(store[fd]);
		store[fd] = NULL;
		return (NULL);
	}
	store[fd] = gnl_get_remainder(store[fd]);
	return (line);
}
