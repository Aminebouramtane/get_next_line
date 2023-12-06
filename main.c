#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example_file.txt", O_RDONLY | O_CREAT);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    line = get_next_line(fd);
    while (line)
    {
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    return (0);
}
