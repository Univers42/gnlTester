/**
 * this test cause 3 errors from 3 context maybe more likely depending on how many lines or how many files descriptor we want to try out
 * These error is generated or likely due how get_next_line handle generic file descriptors like 0,1,2
 */
#include <stdio.h>

int main()
{
    char *line;
    while ((line = get_next_line(0)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    return (0);
}