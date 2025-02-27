#ifndef MEMORY_USAGE_REPORT_H
#define MEMORY_USAGE_REPORT_H

#include <stddef.h>

// Initialize memory tracking
void init_memory_tracker(void);

// Record an allocation
void track_allocation(size_t size);

// Record a deallocation
void track_deallocation(size_t size);

// Generate a memory usage report
void print_memory_report(void);

// Get current memory allocation
size_t get_current_allocated(void);

// Get peak memory allocation
size_t get_peak_allocated(void);

// Get total allocated memory
size_t get_total_allocated(void);

// Get allocation count
size_t get_allocation_count(void);

#endif // MEMORY_USAGE_REPORT_H
