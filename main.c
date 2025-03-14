#include <stdio.h>
#include <stdlib.h>

char *get_next_line(int fd);

int main() {
    char *line;
    printf("Enter text (CTRL+D to stop):\n");

    while ((line = get_next_line(0))) { // 0 = stdin
        printf("GNL Output: %s", line);
        free(line);
    }

    return 0;
}

//./your_program < input.txt

