#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	if (c == 0)
		return (i);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dst))
		return (0);
	i = 0;
	while (*(s1 + i))
	{
		*(dst + i) = *(s1 + i);
		i++;
	}
	*(dst + i) = 0;
	return (dst);
}

char	*gnl_strjoin(char *line, char *backup)
{
	char	*ret;
	int		index;
	int		backup_index;

	if (!line && !backup)
		return (0);
	if (!line)
		return (ft_strdup(backup));
	ret = (char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(backup) + 1));
	if (!ret)
		return (0);
	index = -1;
	while(line[++index])
		ret[index] = line[index];
	backup_index = -1;
	while(backup[++backup_index])
		ret[index++] = backup[backup_index];
	ret[index] = 0;
	return (ret);
}

char	*get_line(char *backup)
{
	char	*buf;
	char	*line;
	int		line_len;

	line_len = ft_strchr(backup, '\n') + 1;
	printf("%d\n", line_len);
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

int main()
{
	int fd = open("ganadara.txt", O_RDONLY);
	// char	line[151];
	char *line;
	int i = 1;
	
	// while (fd > 0)
	// {
	// 	printf("%zd\n", read(fd, line, 150));
	// 	line[150] = 0;
	// 	printf("%s", line);
	// }

	while (i < 18)
	{
		line = get_next_line(fd);
		printf("line [%d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);

	return (0);

	// char *a;
	// a = 0;
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
	// char *c = gnl_strjoin(a, b);
	// printf("%s", c);
	// return (0);
}