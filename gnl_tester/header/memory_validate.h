#ifndef MEMORY_VALIDATE_H
#define MEMORY_VALIDATE_H

#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

// Function to check for memory corruption in a buffer
bool check_memory_corruption(const char *buffer, size_t len);

// Function to validate a specific get_next_line implementation
bool validate_gnl_implementation(void);

// Function to validate a string allocation
bool validate_string(const char *str);

#endif // MEMORY_VALIDATE_H
