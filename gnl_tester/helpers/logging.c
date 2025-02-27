/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:56 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:57 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    
    if (log_fp != NULL) {
        fclose(log_fp);
    }
    
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "outputs/logs/%s", filename ? filename : "default.log");
    
    log_fp = fopen(full_path, "w");
    if (log_fp == NULL) {
        fprintf(stderr, "Error opening log file %s: %s\n", 
                full_path, strerror(errno));
        return false;
    }
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
    fprintf(log_fp, "=== GNL Test Log Started at %s ===\n\n", time_str);
    fflush(log_fp);
    
    return true;
}

void log_message(LogLevel level, const char *format, ...) {
    // Validate inputs
    if (format == NULL) {
        return;
    }
    
    if (log_fp == NULL) {
        init_logging("gnl_test.log");
        if (log_fp == NULL) return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[20];
    strftime(time_str, 20, "%H:%M:%S", tm_info);
    
    fprintf(log_fp, "[%s] [%s] ", log_level_strings[level], time_str);
    
    va_list args;
    va_start(args, format);
    vfprintf(log_fp, format, args);
    va_end(args);
    
    size_t len = strlen(format);
    if (len > 0 && format[len - 1] != '\n') {
        fprintf(log_fp, "\n");
    }
    
    fflush(log_fp);
}

void close_logging(void) {
    if (log_fp != NULL) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char time_str[26];
        strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        
        fprintf(log_fp, "\n=== GNL Test Log Closed at %s ===\n", time_str);
        
        fclose(log_fp);
        log_fp = NULL;
    }
}
