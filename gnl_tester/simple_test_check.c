#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This is a minimal test program to verify if your get_next_line function works at all.
 * It creates a simple test file and then tries to read it line by line.
 */
int main(void) {
    printf("=== Simple GNL Test ===\n\n");
    
    // Create a simple test file
    FILE *f = fopen("simple_test.txt", "w");
    if (!f) {
        printf("Error creating test file\n");
        return 1;
    }
    
    printf("Creating test file...\n");
    fprintf(f, "Line 1\nLine 2\nLine 3\n");
    fclose(f);
    
    // Test get_next_line
    int fd = open("simple_test.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening test file\n");
        return 1;
    }
    
    char *line;
    int line_count = 0;
    printf("Reading file with get_next_line...\n\n");
    
    while ((line = get_next_line(fd)) != NULL) {
        line_count++;
        printf("Line %d: '%s'", line_count, line);
        free(line);
    }
    
    close(fd);
    printf("\nTest completed! Read %d lines.\n", line_count);
    
    if (line_count == 3) {
        printf("\n✅ PASS: Found the expected 3 lines\n");
    } else {
        printf("\n❌ FAIL: Expected 3 lines, but found %d\n", line_count);
    }
    
    return 0;
}
