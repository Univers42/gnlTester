/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_validate.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:07 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:08 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_VALIDATE_H
#define MEMORY_VALIDATE_H

#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                           MEMORY VALIDATION                                  ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Check if a memory buffer shows signs of corruption
 * 
 * @param buffer Memory buffer to check for corruption patterns
 * @param len Length of the buffer in bytes
 * @return bool true if corruption is detected, false if buffer appears valid
 * @note Checks for specific bit patterns that indicate buffer overflow/corruption
 * @warning Accessing memory outside the buffer range could cause undefined behavior
 */
bool check_memory_corruption(const char *buffer, size_t len);

/**
 * @brief Validate the get_next_line implementation for memory-related issues
 * 
 * @return bool true if implementation passes memory tests, false if problems found
 * @note Creates a test file to trigger potential memory issues
 * @note Tests for buffer overflows, memory leaks, and use-after-free
 * @warning Creates and deletes temporary files in the test_cases directory
 * @warning May allocate memory internally that is freed before returning
 */
bool validate_gnl_implementation(void);

/**
 * @brief Validate if a string was properly allocated and not corrupted
 * 
 * @param str String to validate
 * @return bool true if string is valid, false if corruption detected
 * @note Checks for non-printable characters and other corruption indicators
 * @note Safe to use with NULL input (returns true)
 * @warning Access beyond string boundaries could cause segmentation fault
 */
bool validate_string(const char *str);

#endif // MEMORY_VALIDATE_H
