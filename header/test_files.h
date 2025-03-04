/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_files.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:12 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:13 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FILES_H
#define TEST_FILES_H

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                          TEST FILES CONFIGURATION                            ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Number of test file pairs in the TEST_FILES array
 * @note Must be kept in sync with the actual array size
 * @warning Update this value if you add or remove test files
 */
#define TEST_FILES_COUNT 42

/**
 * @brief Global array of test file pairs [input_file, expected_output_file]
 * 
 * @note Each entry contains two strings:
 *       1. Path to input file to read with get_next_line
 *       2. Path to expected output file for comparison
 *       
 * @note Used to automatically test get_next_line with various files and edge cases
 * @note The array is defined in helpers/test_files.c
 * @note To add a new test, add the paths to this array and update TEST_FILES_COUNT
 */
extern const char *TEST_FILES[][2];

#endif // TEST_FILES_H
