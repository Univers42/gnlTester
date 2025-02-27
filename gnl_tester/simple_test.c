#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void) {
    printf("Simple GNL Test\n");
    
    // Create a simple test file
    FILE *f = fopen("simple_test.txt", "w");
    if (!f) {
        printf("Error creating test file\n");
        return 1;
    }
    
    fprintf(f, "Line 1\nLine 2\nLine 3\n");
    fclose(f);
    
    // Test get_next_line
    int fd = open("simple_test.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening test file\n");
        return 1;
    }
    
    char *line;
    printf("Reading file with get_next_line...\n");
    
    while ((line = get_next_line(fd)) != NULL) {
        printf("Read: %s", line);
        free(line);
    }
    
    close(fd);
    printf("Test completed\n");
    
    return 0;
}
