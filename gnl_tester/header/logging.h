/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:59 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:00 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdbool.h>

/**
 * @brief Log levels for different severity of messages
 */
typedef enum {
    LOG_LEVEL_DEBUG,      ///< Detailed debug information
    LOG_LEVEL_INFO,       ///< General informational messages
    LOG_LEVEL_WARNING,    ///< Warning conditions
    LOG_LEVEL_ERROR,      ///< Error conditions
    LOG_LEVEL_CRITICAL    ///< Critical conditions requiring immediate attention
} LogLevel;

/**
 * @brief Initialize the logging system
 * 
 * @param filename Path to the log file
 * @return bool true if initialization successful, false otherwise
 */
bool init_logging(const char *filename);

/**
 * @brief Log a message with the specified severity level
 * 
 * @param level Severity level of the message
 * @param format Format string for the message
 * @param ... Variable arguments for the format string
 */
void log_message(LogLevel level, const char *format, ...);

/**
 * @brief Log a debug message
 */
#define LOG_DEBUG(format, ...) log_message(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)

/**
 * @brief Log an informational message
 */
#define LOG_INFO(format, ...) log_message(LOG_LEVEL_INFO, format, ##__VA_ARGS__)

/**
 * @brief Log a warning message
 */
#define LOG_WARNING(format, ...) log_message(LOG_LEVEL_WARNING, format, ##__VA_ARGS__)

/**
 * @brief Log an error message
 */
#define LOG_ERROR(format, ...) log_message(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

/**
 * @brief Log a critical message
 */
#define LOG_CRITICAL(format, ...) log_message(LOG_LEVEL_CRITICAL, format, ##__VA_ARGS__)

/**
 * @brief Close the logging system and flush any pending logs
 */
void close_logging(void);

#endif // LOGGING_H
