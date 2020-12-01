#include "get_next_line.h"

int main()
{
    int     fd;
    char    *line;

    fd = open("/Users/vping/42projects/get_next_line/text.txt", O_RDONLY);
    while (get_next_line(fd, &line)) {
        printf("%s\n\n", line);
        free(line);
    }
	free(line);
    return (0);
}
