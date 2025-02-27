/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:46 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:38:47 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

#include <stdbool.h>
#include <pthread.h>
#include <stddef.h>

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                         GLOBAL STATE VARIABLES                               ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Flag to signal animation thread to stop
 * @note Set to true when animation should terminate
 * @note Accessed from multiple threads (use mutex for writes)
 */
extern bool stop_animation;

/**
 * @brief Total number of tests that will be executed
 * @note Used for progress calculation and display
 * @note Set once at the beginning of testing
 */
extern size_t total_test_count;

/**
 * @brief Number of tests that have been completed so far
 * @note Used to calculate progress percentage
 * @note Incremented after each test completes
 * @note Accessed from multiple threads (use mutex for modification)
 */
extern size_t completed_tests;

/**
 * @brief Mutex for thread-safe access to progress variables
 * @note Lock before reading/writing progress tracking variables
 * @note Remember to unlock after access is complete
 */
extern pthread_mutex_t progress_mutex;

/**
 * @brief Name of the current test being executed
 * @note Used in progress display
 * @note Updated for each test file
 * @note Maximum 100 characters including null terminator
 * @note Accessed from multiple threads (use mutex for writes)
 */
extern char current_test_name[100];

/**
 * @brief Flag to force completion of tests regardless of status
 * @note Set to true to terminate testing early
 * @note Useful for handling timeout or user interruption
 */
extern bool force_complete;

#endif // GLOBALS_H