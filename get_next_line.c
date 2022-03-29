/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:24 by jihyukim          #+#    #+#             */
/*   Updated: 2022/03/29 17:54:35 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

int main()
{
	int fd = open("ganadara.txt", O_RDONLY);
	char	*line;
	int i = 1;
	
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("line [%d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);

	return (0);

	// char *a;
	// a = malloc(7);
	// int i = 0;
	// while (i < 7)
	// {
	// 	a[i] = i + 48;
	// 	i++;
	// }
	// char *b;
	// b = malloc(7);
	// i = 0;
	// int j = 'a';
	// while (i < 7)
	// {
	// 	b[i] = j++;
	// 	i++;
	// };
	// char *c = ft_strjoin(a, b);
	// printf("%s", c);
	// return (0);
}
