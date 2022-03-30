/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/03/30 18:30:01 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *backup)
{
	char	*buf;
	char	*line;
	int		line_len;

	line_len = ft_strchr(backup, '\n');
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (0);
	buf = backup;
	ft_strlcpy(line, buf, line_len + 1);
	ft_strlcpy(backup, buf + line_len, ft_strlen(buf) - line_len + 1);
	return (line);
}

char	*get_until_newline(int fd, char *backup)
{
	char	*line_merged;
	char	*buf;
	int		bytes_read;

	line_merged = 0;
	buf = 0;
	bytes_read = 1;
	if (ft_strchr(backup, '\n'))
		return (get_line(backup));
	line_merged = gnl_strjoin(line_merged, backup);
	while (!(ft_strchr(line_merged, '\n')))
	{
		bytes_read = read(fd, backup, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		if (ft_strchr(backup, '\n'))
		{
			buf = get_line(backup);
			line_merged = gnl_strjoin(line_merged, buf);
			free(buf);
			return (line_merged);
		}
		line_merged = gnl_strjoin(line_merged, backup);
	}
	return (line_merged);
}	

char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = 1;
	if (backup[0] == 0)
		bytes_read = read(fd, backup, BUFFER_SIZE);
	line = 0;
	if (bytes_read > 0)
	{
		line = get_until_newline(fd, backup);
		if (!line)
			return (0);
	}
	return (line);
}
