#ifndef LOGGING_H
#define LOGGING_H

#include <stdbool.h>

// Log levels
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

// Initialize logging to a specific file
bool init_logging(const char *filename);

// Log a message with the specified level
void log_message(LogLevel level, const char *format, ...);

// Close and clean up logging
void close_logging(void);

// Convenience macros for different log levels
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) log_message(LOG_WARNING, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) log_message(LOG_CRITICAL, fmt, ##__VA_ARGS__)

#endif // LOGGING_H
