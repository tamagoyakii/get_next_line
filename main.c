#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{	
	int fd = open("ganadara.txt", O_RDONLY);
	char *line;
	int i;

	line = 0;
	i = 1;
	while ((line = get_next_line(fd)) > 0)
	{
		printf("line [%d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);

	return (0);
}
