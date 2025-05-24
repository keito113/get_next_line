/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:01 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/24 18:00:54 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin_free(char *store, const char *buf)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	len = gnl_strlen(store);
	if (len > SIZE_MAX - gnl_strlen(buf) - 1)
		return (NULL);
	new_str = malloc(len + gnl_strlen(buf) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = store[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		new_str[len + i] = buf[i];
		i++;
	}
	new_str[len + i] = '\0';
	free(store);
	return (new_str);
}

ssize_t	gnl_newline_index(const char *store)
{
	ssize_t	i;

	if (!store)
		return (-1);
	i = 0;
	while (store[i])
	{
		if (store[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_clip_line(char *store)
{
	ssize_t	len;
	size_t	i;
	size_t	cpy_len;
	char	*clip;

	if (!store)
		return (NULL);
	len = gnl_newline_index(store);
	cpy_len = 0;
	if (len >= 0)
		cpy_len = len + 1;
	else
		cpy_len = gnl_strlen(store);
	clip = malloc(cpy_len + 1);
	if (!clip)
		return (NULL);
	i = 0;
	while (i < cpy_len)
	{
		clip[i] = store[i];
		i++;
	}
	clip[i] = '\0';
	return (clip);
}

char	*gnl_get_remainder(char *store)
{
	ssize_t	idx;
	size_t	rem_len;
	size_t	i;
	char	*clip;

	if (!store)
		return (NULL);
	idx = gnl_newline_index(store);
	if (idx < 0)
		return (free(store), NULL);
	rem_len = (gnl_strlen(store)) - (idx + 1);
	if (rem_len == 0)
		return (free(store), NULL);
	clip = malloc(rem_len + 1);
	if (!clip)
		return (free(store), NULL);
	i = 0;
	while (i < rem_len)
	{
		clip[i] = store[(idx + 1) + i];
		i++;
	}
	clip[rem_len] = '\0';
	free(store);
	return (clip);
}
