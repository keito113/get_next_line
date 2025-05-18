/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:27:10 by keitabe           #+#    #+#             */
/*   Updated: 2025/05/18 13:50:35 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
char	*gnl_strjoin_free(char *stor, const char *buf);
ssize_t	gnl_newline_index(const char *stor);
char	*gnl_clip_line(const char *stor);
char	*gnl_remain_re(char *stor);

#endif
