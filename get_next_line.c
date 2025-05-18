/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:06 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/18 14:22:28 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store;
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		byt_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	byt_read = 0;
	while (gnl_newline_index(store) < 0 && (byt_read = read(fd, buf,
				BUFFER_SIZE)) > 0)
	{
		buf[byt_read] = '\0';
		if (!(store = gnl_strjoin_free(store, buf)))
			return (NULL);
	}
	if (byt_read < 0)
		return (free(store), store = NULL, NULL);
	line = gnl_clip_line(store);
	store = gnl_get_remainder(store);
	return (line);
}
