/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:00:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/13 17:09:50 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_bzero(char *backup)
{
	int	index;

	index = -1;
	while (backup[++index])
		backup[index] = 0;
}

char	*get_line(char *line_merged, char *backup)
{
	char	*line;
	int		line_len;

	line_len = gnl_strchr(line_merged);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (0);
	gnl_strlcpy(line, line_merged, line_len + 1);
	gnl_strlcpy(backup, line_merged + line_len,
		ft_strlen(line_merged) - line_len + 1);
	free(line_merged);
	line_merged = 0;
	return (line);
}

char	*get_until_newline(char *line_merged, char *backup)
{
	char	*ret;

	ret = 0;
	if (gnl_strchr(line_merged))
		return (line_merged);
	ret = gnl_strjoin(line_merged, backup);
	gnl_bzero(backup);
	free(line_merged);
	line_merged = 0;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	backup[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line_merged;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = 1;
	if (backup[fd][0] == 0)
		bytes_read = read(fd, backup[fd], BUFFER_SIZE);
	if (bytes_read <= 0)
		return (0);
	line_merged = gnl_strjoin("", "");
	while (bytes_read > 0)
	{
		line_merged = get_until_newline(line_merged, backup[fd]);
		if (gnl_strchr(line_merged))
			return (get_line(line_merged, backup[fd]));
		if (backup[fd][0] == 0)
			bytes_read = read(fd, backup[fd], BUFFER_SIZE);
	}
	return (line_merged);
}
