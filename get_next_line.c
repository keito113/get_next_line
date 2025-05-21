/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:06 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/21 13:34:34 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	store = read_or_free(fd, store);
	if (!store)
		return (NULL);
	line = gnl_clip_line(store);
	if (!line)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	store = gnl_get_remainder(store);
	return (line);
}
