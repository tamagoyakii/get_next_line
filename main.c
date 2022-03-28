#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int BUFFER_SIZE = 100;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

size_t	ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char) c)
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
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize > 0)
		*(dst + i) = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	i = 0;
	while (dst_len + i + 1 < dstsize && *(src + i))
	{
		*(dst + dst_len + i) = *(src + i);
		i++;
	}
	*(dst + dst_len + i) = 0;
	return (src_len + dst_len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcat(ret + s1_len, s2, s1_len + s2_len);
	return (ret);
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

// char	*get_backup(char *full_line)
// {
// 	char	*backup;
// 	size_t	line_len;
// 	size_t	backup_len;

// 	line_len = ft_strchr(full_line, '\n') + 1;
// 	backup_len = ft_strlen(full_line) - line_len;
// 	backup = (char *)malloc(sizeof(char) * (backup_len + 1));
// 	if (!backup)
// 		return (0);
// 	ft_strlcpy(backup, full_line + line_len, backup_len + 1);
// 	return (backup);
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
	// backup = get_backup(full_line);
	// free(full_line);
	// full_line = 0;
	return (line);
}



int main()
{
	int fd = open("ganadara.txt", O_RDWR);
	printf("%d\n", fd);

	// char	*buf;
	// buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// if (!buf)
	// 	return (0);
	// read(fd, buf, BUFFER_SIZE);
	// printf("%s\n", buf);

	printf("%s\n", get_next_line(fd));

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