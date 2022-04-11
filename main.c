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

size_t	gnl_strchr(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	while (src[++i] && i + 1 < dstsize)
		dst[i] = src[i];
	if (dstsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ret))
		return (0);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

char	*gnl_strjoin(char *line, char *backup)
{
	char	*ret;
	int		index;
	int		backup_index;

	if (!line && !backup)
		return (0);
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

void	gnl_bzero(char *backup)
{
	int	index;

	index = -1;
	while (backup[++index])
		backup[index] = 0;	
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
			break;
		if (backup[0] == 0)
			bytes_read = read(fd, backup, BUFFER_SIZE);
	}
	if (bytes_read == 0)
		return (line_merged);
	return (get_line(line_merged, backup));
}

int main()
{
	int fd = open("ganadara.txt", O_RDONLY);
	char *line;
	int i = 1;

	printf("1\n");
	line = 0;
	while (i < 62)
	{
		line = get_next_line(fd);
		printf("line [%d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}