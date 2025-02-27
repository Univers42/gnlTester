#include "../header/logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

// Global log file pointer
static FILE *log_fp = NULL;

// Log levels as strings
static const char *log_level_strings[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

// Initialize logging system
bool init_logging(const char *filename) {
    // Create logs directory if it doesn't exist
    struct stat st = {0};
    if (stat("outputs", &st) == -1) {
        mkdir("outputs", 0700);
    }
    if (stat("outputs/logs", &st) == -1) {
        mkdir("outputs/logs", 0700);
    }
    
    // Close existing log file if open
    if (log_fp != NULL) {
        fclose(log_fp);
    }
    
    // Construct full path
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "outputs/logs/%s", filename ? filename : "default.log");
    
    // Open log file
    log_fp = fopen(full_path, "w");
    if (log_fp == NULL) {
        // Fall back to stderr if file can't be opened
        fprintf(stderr, "Error opening log file %s: %s\n", 
                full_path, strerror(errno));
        return false;
    }
    
    // Write log header
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(log_fp, "=== GNL Test Log Started at %s ===\n\n", time_str);
    fflush(log_fp);
    
    return true;
}

// Log a message with specified level
void log_message(LogLevel level, const char *format, ...) {
    // Validate inputs
    if (format == NULL) {
        return;  // Don't log anything if format is NULL
    }
    
    if (log_fp == NULL) {
        // Initialize log file if not already done
        init_logging("gnl_test.log");
        if (log_fp == NULL) return;  // Still can't log
    }
    
    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, 20, "%H:%M:%S", tm_info);
    
    // Print log level and timestamp
    fprintf(log_fp, "[%s] [%s] ", log_level_strings[level], time_str);
    
    // Print actual message with variable arguments
    va_list args;
    va_start(args, format);
    vfprintf(log_fp, format, args);
    va_end(args);
    
    // Add newline if not present and format is not empty
    size_t len = strlen(format);
    if (len > 0 && format[len - 1] != '\n') {
        fprintf(log_fp, "\n");
    }
    
    // Ensure log is written to disk
    fflush(log_fp);
}

// Cleanup logging system
void close_logging(void) {
    if (log_fp != NULL) {
        // Add log footer
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char time_str[26];
        strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        
        fprintf(log_fp, "\n=== GNL Test Log Closed at %s ===\n", time_str);
        
        fclose(log_fp);
        log_fp = NULL;
    }
}
