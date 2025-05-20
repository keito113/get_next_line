/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:06 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/20 11:08:57 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_or_free(int fd, char *store)
{
	ssize_t	i;
	char	buf[BUFFER_SIZE + 1];

	i = 0;
	while (gnl_newline_index(store) < 0 && (i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!(store = gnl_strjoin_free(store, buf)))
			return (NULL);
	}
	if (i < 0)
	{
		free(store);
		return (NULL);
	}
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	store = read_or_free(fd, store);
	if (!store)
		return (NULL);
	line = gnl_clip_line(store);
	if (!line)
	{
		store = NULL;
		return (NULL);
	}
	store = gnl_get_remainder(store);
	return (line);
}
