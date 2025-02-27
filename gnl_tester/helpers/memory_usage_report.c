/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_usage_report.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:40:06 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:40:07 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/memory_usage_report.h"
#include "../header/logging.h"
#include <stdio.h>
#include <string.h>

#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

static size_t total_allocated = 0;
static size_t current_allocated = 0;
static size_t allocation_count = 0;
static size_t peak_allocated = 0;

void init_memory_tracker(void) {
    total_allocated = 0;
    current_allocated = 0;
    allocation_count = 0;
    peak_allocated = 0;
    
    LOG_INFO("Memory tracker initialized");
}

void track_allocation(size_t size) {
    total_allocated += size;
    current_allocated += size;
    allocation_count++;
    
    if (current_allocated > peak_allocated) {
        peak_allocated = current_allocated;
    }
    
    LOG_DEBUG("Allocation of %zu bytes (current: %zu, peak: %zu)", 
             size, current_allocated, peak_allocated);
}

void track_deallocation(size_t size) {
    if (size <= current_allocated) {
        current_allocated -= size;
    } else {
        LOG_ERROR("Memory tracking error: freeing %zu bytes but only %zu allocated", 
                 size, current_allocated);
        current_allocated = 0;
    }
    
    LOG_DEBUG("Deallocation of %zu bytes (current: %zu)", 
             size, current_allocated);
}

void print_memory_report(void) {
    printf("\n" CYAN "     ╭──────────────────────────────────────────╮" RESET "\n");
    printf(CYAN "     │" RESET BOLD "  Memory Usage Report                    " RESET CYAN "│" RESET "\n");
    printf(CYAN "     ├──────────────────────────────────────────┤" RESET "\n");
    printf(CYAN "     │" RESET " Total allocated:    %10zu bytes      " CYAN "│" RESET "\n", total_allocated);
    printf(CYAN "     │" RESET " Peak usage:         %10zu bytes      " CYAN "│" RESET "\n", peak_allocated);
    printf(CYAN "     │" RESET " Allocation count:   %10zu            " CYAN "│" RESET "\n", allocation_count);
    
    if (current_allocated > 0) {
        printf(CYAN "     │" RESET RED " Leaked memory:      %10zu bytes      " CYAN "│" RESET "\n", current_allocated);
    } else {
        printf(CYAN "     │" RESET GREEN " All memory properly freed!               " CYAN "│" RESET "\n");
    }
    
    double efficiency = 0.0;
    if (total_allocated > 0) {
        efficiency = 100.0 - ((double)total_allocated - peak_allocated) / total_allocated * 100.0;
        if (efficiency < 0) efficiency = 0;
        if (efficiency > 100) efficiency = 100;
    }
    
    printf(CYAN "     │" RESET " Memory efficiency:  %10.1f%%           " CYAN "│" RESET "\n", efficiency);
    
    double extra_percent = (efficiency < 90.0) ? 100.0 - efficiency : 0.0;
    if (extra_percent > 15.0) {
        printf(CYAN "     │                                          │" RESET "\n");
        printf(CYAN "     │" RESET YELLOW " Warning: Excessive memory allocation      " CYAN "│" RESET "\n");
        printf(CYAN "     │" RESET YELLOW " (+20 in strndup is inefficient)          " CYAN "│" RESET "\n");
    }
    
    printf(CYAN "     ╰──────────────────────────────────────────╯" RESET "\n\n");
}

size_t get_current_allocated(void) {
    return current_allocated;
}

size_t get_peak_allocated(void) {
    return peak_allocated;
}

size_t get_total_allocated(void) {
    return total_allocated;
}

size_t get_allocation_count(void) {
    return allocation_count;
}
