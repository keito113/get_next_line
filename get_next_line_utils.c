/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:01 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/17 15:22:48 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin_free(char *stor, const char *buf)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*new_str;

	len1 = gnl_strlen(stor);
	len2 = gnl_strlen(buf);
	if (len1 > SIZE_MAX - len2 - 1)
		return (free(stor), NULL);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (free(stor), NULL);
	i = 0;
	while (i < len1)
		new_str[i] = stor[i++];
	j = 0;
	while (j < len2)
		new_str[i + j] = buf[j++];
	new_str[i + j] = '\0';
	free(stor);
	return (new_str);
}

ssize_t	gnl_newline_index(const char *stor)
{
	ssize_t	i;

	if (!stor)
		return (-1);
	i = 0;
	while (stor[i])
	{
		if (stor[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_clip_line(const char *stor)
{
	ssize_t	len;
	size_t	i;
	size_t	cpy_len;
	char	*clip;

	if (!stor)
		return (NULL);
	len = gnl_newline_index(stor);
	cpy_len = 0;
	if (len >= 0)
		cpy_len = len + 1;
	else
		cpy_len = gnl_strlen(stor);
	clip = malloc(cpy_len + 1);
	if (!clip)
		return (free(stor), NULL);
	i = 0;
	while (i < cpy_len)
	{
		clip[i] = stor[i];
		i++;
	}
	clip[i] = '\0';
	return (clip);
}

char	*gnl_remain_re(char *stor)
{
	ssize_t	idx;
	size_t	len;
	size_t	rem_len;
	size_t	i;
	char	*clip;

	if (!stor)
		return (NULL);
	idx = gnl_newline_index(stor);
	if (idx < 0)
		return (free(stor), NULL);
	len = gnl_strlen(stor);
	rem_len = len - (idx + 1);
	if (rem_len == 0)
		return (free(stor), NULL);
	clip = malloc(rem_len + 1);
	if (!clip)
		return (free(stor), NULL);
	i = 0;
	while (i < rem_len)
		clip[i] = stor[(idx + 1) + i++];
	clip[rem_len] = '\0';
	free(stor);
	return (clip);
}
