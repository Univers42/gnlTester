#include "../header/memory_validate.h"
#include "../header/defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pattern used to detect buffer overflows - used in check_memory_corruption
static const unsigned char BUFFER_PATTERN[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};

// Check if a memory block has been corrupted - safer implementation
bool check_memory_corruption(const char *buffer, size_t len) {
    if (!buffer) return false;
    
    // Only check valid memory within the buffer - don't go beyond len
    for (size_t i = 0; i + 3 < len; i++) {
        // Look for patterns that shouldn't be in valid strings
        // Compare with first 4 bytes of our known corruption pattern (safer)
        if ((unsigned char)buffer[i] == BUFFER_PATTERN[0] && 
            (unsigned char)buffer[i+1] == BUFFER_PATTERN[1] &&
            (unsigned char)buffer[i+2] == BUFFER_PATTERN[2] &&
            (unsigned char)buffer[i+3] == BUFFER_PATTERN[3]) {
            return true;  // Found corruption pattern
        }
    }
    return false;
}

// Forward declaration of get_next_line function
extern char *get_next_line(int fd);

// Validate a specific get_next_line implementation
bool validate_gnl_implementation(void) {
    // Test file specifically designed to trigger the memory error
    const char *test_file = "test_cases/memory_test.txt";
    int fd;
    char *line;
    bool error_found = false;
    
    // Create a test file that will trigger the issue
    FILE *f = fopen(test_file, "w");
    if (!f) {
        fprintf(stderr, "Could not create memory test file\n");
        return false;
    }
    
    // Write a pattern that will cause the +6 issue to be visible
    fprintf(f, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    fclose(f);
    
    fd = open(test_file, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Could not open memory test file\n");
        return false;
    }
    
    // First line should be read normally
    line = get_next_line(fd);
    if (!line) {
        fprintf(stderr, "get_next_line returned NULL unexpectedly\n");
        close(fd);
        return false;
    }
    
    // Only check for obvious memory corruption (accessing only valid memory)
    size_t line_len = strlen(line);
    if (line_len > 0) {
        // Check if string ends with unexpected characters
        if (line[line_len-1] != '\n' && line[line_len-1] != 'a') {
            fprintf(stderr, "Possible memory corruption: unexpected character at end of buffer\n");
            error_found = true;
        }
    }
    
    free(line);
    
    // Second line might reveal the "+6" issue
    line = get_next_line(fd);
    if (!line) {
        fprintf(stderr, "get_next_line returned NULL on second line\n");
        close(fd);
        return false;
    }
    
    // Safe check again
    line_len = strlen(line);
    if (line_len > 0) {
        // Check if string ends with unexpected characters
        if (line[line_len-1] != '\n' && line[line_len-1] != 'b') {
            fprintf(stderr, "Possible memory corruption: unexpected character at end of buffer\n");
            error_found = true;
        }
    }
    
    free(line);
    close(fd);
    
    return !error_found;
}

// Check if a string has been properly allocated
bool validate_string(const char *str) {
    if (!str) return true;  // NULL is valid in certain contexts
    
    size_t len = strlen(str);
    
    // Only do simple checks without accessing memory beyond the string
    // Check if the string seems valid (contains only expected characters)
    for (size_t i = 0; i < len; i++) {
        // Check for obviously corrupted memory (non-printable characters)
        // Exclude newline and normal whitespace
        if ((str[i] < 32 || str[i] > 126) && 
            str[i] != '\n' && str[i] != '\t' && str[i] != '\r') {
            fprintf(stderr, "String contains unexpected characters (possible corruption)\n");
            return false;
        }
    }
    
    return true;
}
