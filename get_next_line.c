/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/11 18:14:54 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_bzero(char *backup)
{
	int	index;

	index = -1;
	while (backup[++index])
		backup[index] = 0;
}

char	*get_line(char *line_merged, char *backup)
{
	char	*buf;
	char	*line;
	int		line_len;

	line_len = gnl_strchr(line_merged) + 1;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (0);
	buf = ft_strdup(line_merged);
	line_merged = 0;
	ft_strlcpy(line, buf, line_len + 1);
	ft_strlcpy(backup, buf + line_len, ft_strlen(buf) - line_len + 1);
	buf = 0;
	free(buf);
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
	line_merged = 0;
	free(line_merged);
	return (ret);
}	

char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1];
	char		*line_merged;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = 1;
	if (backup[0] == 0)
		bytes_read = read(fd, backup, BUFFER_SIZE);
	line_merged = ft_strdup("");
	while (bytes_read > 0)
	{
		line_merged = get_until_newline(line_merged, backup);
		if (gnl_strchr(line_merged))
			break ;
		if (backup[0] == 0)
			bytes_read = read(fd, backup, BUFFER_SIZE);
	}
	if (bytes_read == 0)
		return (line_merged);
	return (get_line(line_merged, backup));
}
