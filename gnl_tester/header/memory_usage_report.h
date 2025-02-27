/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_usage_report.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:03 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:04 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_USAGE_REPORT_H
#define MEMORY_USAGE_REPORT_H

#include <stddef.h>

/**
 * @brief Initialize the memory tracking system
 * Resets all counters and prepares for tracking allocations
 */
void init_memory_tracker(void);

/**
 * @brief Record a memory allocation operation
 * 
 * @param size Size in bytes of the allocated memory
 */
void track_allocation(size_t size);

/**
 * @brief Record a memory deallocation operation
 * 
 * @param size Size in bytes of the freed memory
 */
void track_deallocation(size_t size);

/**
 * @brief Generate and display a report of memory usage
 * Shows allocation stats, potential leaks, and efficiency rating
 */
void print_memory_report(void);

/**
 * @brief Get the current amount of allocated memory
 * 
 * @return size_t Number of bytes currently allocated
 */
size_t get_current_allocated(void);

/**
 * @brief Get the peak memory usage during program execution
 * 
 * @return size_t Maximum number of bytes allocated at any point
 */
size_t get_peak_allocated(void);

/**
 * @brief Get the total memory allocated during program execution
 * 
 * @return size_t Total bytes allocated (including freed memory)
 */
size_t get_total_allocated(void);

/**
 * @brief Get the number of allocation operations performed
 * 
 * @return size_t Count of memory allocation calls
 */
size_t get_allocation_count(void);

#endif // MEMORY_USAGE_REPORT_H
