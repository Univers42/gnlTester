#ifndef LOGGING_H
#define LOGGING_H

#include <stdbool.h>

// Define log levels
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL
} LogLevel;

// Initialize logging system
bool init_logging(const char *filename);

// Log a message
void log_message(LogLevel level, const char *format, ...);

// Convenience macros for different log levels
#define LOG_DEBUG(format, ...) log_message(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) log_message(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) log_message(LOG_LEVEL_WARNING, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) log_message(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_CRITICAL(format, ...) log_message(LOG_LEVEL_CRITICAL, format, ##__VA_ARGS__)

// Clean up logging
void close_logging(void);

#endif // LOGGING_H
