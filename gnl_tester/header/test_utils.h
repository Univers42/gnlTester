/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:18 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:19 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "defines.h"
#include "globals.h"

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                               TEST MACROS                                    ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Announces the start of a test function with emoji and function name
 * @note Used at the beginning of test functions for visual separation
 */
#define TEST_START() printf("\n🔄 %s\n", __func__)

/**
 * @brief Tests get_next_line with expected output and reports result
 * 
 * @param fd File descriptor to read from
 * @param expected Expected string output
 * @note This macro handles memory cleanup automatically
 * @warning Will report failure if get_next_line returns NULL unexpectedly
 */
#define TEST_GNL(fd, expected) do {                                             \
    char *line = get_next_line(fd);                                             \
    if (compare_output(expected, line) == 0) {                                  \
        printf("✅ Test passed: line matches expected output\n");               \
    } else {                                                                    \
        printf("❌ Test failed:\nExpected: %s\nGot: %s\n", expected, line);     \
    }                                                                           \
    free(line);                                                                 \
} while(0)

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                             UTILITY FUNCTIONS                                ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Compare expected output with actual output from get_next_line
 * 
 * @param expected The expected string to be returned by get_next_line
 * @param actual The actual string returned by get_next_line
 * @return int 0 if strings match exactly, non-zero if they differ
 * @note Handles NULL values safely
 * @note This performs exact comparison, including newlines and null terminators
 */
int compare_output(const char *expected, const char *actual);

/**
 * @brief Run a test with specified file descriptor and expected output
 * 
 * @param fd File descriptor to read from using get_next_line
 * @param expected Expected string to be returned by get_next_line
 * @note Prints detailed success/failure information to stdout
 * @note Will free memory returned by get_next_line
 */
void run_test(int fd, const char *expected);

/**
 * @brief Compare two files to check if their contents match exactly
 * 
 * @param file1 Path to the first file
 * @param file2 Path to the second file (usually the expected output)
 * @return int 1 if files match exactly, 0 if they differ in any way
 * @note Files are compared byte by byte
 * @warning Returns 0 (fail) if either file cannot be opened
 */
int compare_files(const char *file1, const char *file2);

#endif // TEST_UTILS_H
