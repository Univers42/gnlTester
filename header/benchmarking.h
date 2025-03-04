/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmarking.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:25 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:38:27 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARKING_H
#define BENCHMARKING_H

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <sys/time.h>

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                           BENCHMARK DATA STRUCTURE                           ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Structure to hold comprehensive benchmark results
 */
typedef struct {
    size_t memory_peak;      ///< Peak memory usage in KB
    size_t memory_leaks;     ///< Estimated memory leaks in bytes
    double time_elapsed;     ///< Total elapsed time in seconds
    double efficiency_score; ///< Overall implementation efficiency score (0-100)
    double buffer_efficiency; ///< Performance consistency across buffer sizes (0-100)
    double edge_case_score;  ///< Edge case handling effectiveness score (0-100)
} BenchmarkResults;

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                           BENCHMARKING FUNCTIONS                             ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Start benchmarking session and initialize all performance counters
 * 
 * @note Call this once at the beginning of your test suite
 * @note Resets all internal counters and starts the timer
 * @note Uses gettimeofday for high-precision timing
 */
void start_benchmark(void);

/**
 * @brief Track a memory allocation for performance analysis
 * 
 * @param size Size in bytes of the allocated memory
 * @note Increases allocation count and updates memory peak if needed
 * @note Should be called each time memory is allocated via malloc/calloc/realloc
 */
void benchmark_track_alloc(size_t size);

/**
 * @brief Track a memory deallocation for leak detection
 * 
 * @param size Size in bytes of the freed memory
 * @note Updates internal counters to track potential memory leaks
 * @note Should be called each time memory is freed via free
 * @warning Ensure the size matches what was previously allocated
 */
void benchmark_track_free(size_t size);

/**
 * @brief Stop benchmarking and calculate final performance metrics
 * 
 * @param all_tests_passed Whether all functional tests have passed
 * @param buffer_efficiency Performance consistency score across buffer sizes
 * @note Call this once at the end of your test suite
 * @note Calculates memory efficiency, time efficiency and overall score
 */
void stop_benchmark(bool all_tests_passed, double buffer_efficiency);

/**
 * @brief Get the current detailed benchmark results structure
 * 
 * @return BenchmarkResults Structure containing all measured performance metrics
 * @note Call this after stop_benchmark to retrieve the final results
 */
BenchmarkResults get_benchmark_results(void);

/**
 * @brief Display formatted benchmark results with star ratings
 * 
 * @note Prints code quality, memory usage, and implementation ratings
 * @note Uses color coding to highlight exceptional or problematic areas
 */
void display_benchmark_results(void);

/**
 * @brief Calculate buffer size efficiency based on timing consistency
 * 
 * @param buffer_times Array of execution times in ms for different buffer sizes
 * @param count Number of timing measurements in the array
 * @return double Consistency score from 0 to 100 (higher is better)
 * @note Higher scores indicate more consistent performance across all buffer sizes
 * @note Uses statistical methods to measure performance variance
 * @warning Requires at least 2 timing measurements to calculate meaningful results
 */
double calculate_buffer_efficiency(size_t *buffer_times, size_t count);

#endif // BENCHMARKING_H
