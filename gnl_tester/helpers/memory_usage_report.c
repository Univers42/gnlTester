#include "../header/memory_usage_report.h"
#include "../header/logging.h"
#include <stdio.h>
#include <string.h>

// Define color macros
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

// Simple memory tracking state
static size_t total_allocated = 0;
static size_t current_allocated = 0;
static size_t allocation_count = 0;
static size_t peak_allocated = 0;

// Initialize memory tracking
void init_memory_tracker(void) {
    total_allocated = 0;
    current_allocated = 0;
    allocation_count = 0;
    peak_allocated = 0;
    
    LOG_INFO("Memory tracker initialized");
}

// Record an allocation
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

// Record a deallocation
void track_deallocation(size_t size) {
    if (size <= current_allocated) {
        current_allocated -= size;
    } else {
        // This is an error - freeing more than allocated
        LOG_ERROR("Memory tracking error: freeing %zu bytes but only %zu allocated", 
                 size, current_allocated);
        current_allocated = 0;
    }
    
    LOG_DEBUG("Deallocation of %zu bytes (current: %zu)", 
             size, current_allocated);
}

// Generate a memory usage report
void print_memory_report(void) {
    printf("\n" CYAN "     ╭──────────────────────────────────────────╮" RESET "\n");
    printf(CYAN "     │" RESET BOLD "  Memory Usage Report                    " RESET CYAN "│" RESET "\n");
    printf(CYAN "     ├──────────────────────────────────────────┤" RESET "\n");
    printf(CYAN "     │" RESET " Total allocated:    %10zu bytes      " CYAN "│" RESET "\n", total_allocated);
    printf(CYAN "     │" RESET " Peak usage:         %10zu bytes      " CYAN "│" RESET "\n", peak_allocated);
    printf(CYAN "     │" RESET " Allocation count:   %10zu            " CYAN "│" RESET "\n", allocation_count);
    
    // Check for memory leaks
    if (current_allocated > 0) {
        printf(CYAN "     │" RESET RED " Leaked memory:      %10zu bytes      " CYAN "│" RESET "\n", current_allocated);
    } else {
        printf(CYAN "     │" RESET GREEN " All memory properly freed!               " CYAN "│" RESET "\n");
    }
    
    // Efficiency rating based on extra allocations
    double efficiency = 0.0;
    if (total_allocated > 0) {
        // Calculate how efficiently memory was used
        // (This is a simplified estimation - real calculation would be more complex)
        efficiency = 100.0 - ((double)total_allocated - peak_allocated) / total_allocated * 100.0;
        if (efficiency < 0) efficiency = 0;
        if (efficiency > 100) efficiency = 100;
    }
    
    printf(CYAN "     │" RESET " Memory efficiency:  %10.1f%%           " CYAN "│" RESET "\n", efficiency);
    
    // Evaluate the excessive allocation in get_leftover
    double extra_percent = (efficiency < 90.0) ? 100.0 - efficiency : 0.0;
    if (extra_percent > 15.0) {
        printf(CYAN "     │                                          │" RESET "\n");
        printf(CYAN "     │" RESET YELLOW " Warning: Excessive memory allocation      " CYAN "│" RESET "\n");
        printf(CYAN "     │" RESET YELLOW " (+20 in strndup is inefficient)          " CYAN "│" RESET "\n");
    }
    
    printf(CYAN "     ╰──────────────────────────────────────────╯" RESET "\n\n");
}

// Get current memory allocation
size_t get_current_allocated(void) {
    return current_allocated;
}

// Get peak memory allocation
size_t get_peak_allocated(void) {
    return peak_allocated;
}

// Get total allocated memory
size_t get_total_allocated(void) {
    return total_allocated;
}

// Get allocation count
size_t get_allocation_count(void) {
    return allocation_count;
}
