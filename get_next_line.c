/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/01/29 19:11:38 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// char	**split_line(char *s)
// {
// 	char	*ret[2];
// 	size_t	front;
// 	size_t	back;

// 	front = ft_strchr(s, '\n') + 1;
// 	back = ft_strlen(s) - front;
// 	ret[0] = (char *)malloc(sizeof(char) * (front + 1));
// 	if (!(ret[0]))
// 		return (0);
// 	ft_strlcpy(&ret[0], s, front + 1);
// 	ret[1] = (char *)malloc(sizeof(char) * (back + 1));
// 	if (!(ret[1]))
// 		return (0);
// 	ft_strlcpy(&ret[1], s + front, back + 1);
// 	return (ret);
// }

char	*get_full_line(int fd, char *full_line)
{
	char	*buf;
	int		bytes_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	bytes_read = 1;
	while (!(ft_strchr(full_line, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buf);
			return (0);
		}
		full_line = ft_strjoin(full_line, buf);
	}
	free(buf);
	return (full_line);
}	

char	*get_line(char *full_line)
{
	char	*line;
	size_t	line_len;
	
	line_len = ft_strchr(full_line, '\n') + 1;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (0);
	ft_strlcpy(line, full_line, line_len + 1);
	return (line);
}

char	*get_backup(char *full_line)
{
	char	*backup;
	size_t	line_len;
	size_t	backup_len;

	line_len = ft_strchr(full_line, '\n') + 1;
	backup_len = ft_strlen(full_line) - line_len;
	backup = (char *)malloc(sizeof(char) * (backup_len + 1));
	if (!backup)
		return (0);
	ft_strlcpy(backup, full_line + line_len, backup_len + 1);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*full_line;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	full_line = get_full_line(fd, full_line);
	if (!full_line)
		return (0);
	line = get_line(full_line);
	backup = get_backup(full_line);
	free(full_line);
	full_line = 0;
	return (line);
}
