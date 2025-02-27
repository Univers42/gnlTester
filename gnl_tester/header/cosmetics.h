/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmetics.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:31 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:38:33 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COSMETICS_H
# define COSMETICS_H
# include "test_utils.h"
# include <stdbool.h>

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                          DISPLAY FUNCTIONS                                   ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Display a success message when all tests pass
 * 
 * @note Shows a congratulatory certificate with ASCII art
 * @note Includes animated elements and colorful celebration graphics
 * @note Call this only when ALL tests have passed
 */
void display_success_message(void);

/**
 * @brief Display the welcome banner at program start
 * 
 * @note Shows the GNL tester logo with cyberpunk styling
 * @note Includes version information and initialization message
 * @note Has a brief delay for visual effect
 */
void display_start_message(void);

/**
 * @brief Display a failure message when any test fails
 * 
 * @note Shows ASCII art indicating failure
 * @note Provides specific debugging tips for common GNL issues
 * @note Uses red color coding to highlight the failure
 * @note Includes encouragement to continue debugging
 */
void display_failure_message(void);

/**
 * @brief Display a header for a group of tests using specific buffer size
 * 
 * @param buffer_size The BUFFER_SIZE value being used for testing
 * @note Creates visual separation between different buffer size tests
 * @note Uses cyan color for visibility
 */
void display_test_header(size_t buffer_size);

/**
 * @brief Display the result of an individual test file
 * 
 * @param filename Name of the test file being evaluated
 * @param success Whether the test has passed (true) or failed (false)
 * @param detailed Whether to show detailed output or abbreviated results
 * @note Uses color-coding: green for success, red for failure
 * @note In non-detailed mode, results are suppressed
 * @note Truncates very long filenames for display purposes
 */
void display_test_result(const char *filename, bool success, bool detailed);

#endif // COSMETICS_H