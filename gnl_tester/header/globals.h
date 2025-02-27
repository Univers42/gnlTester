#ifndef GLOBALS_H
# define GLOBALS_H

#include <stdbool.h>
#include <pthread.h>
#include <stddef.h>

// Global declarations - use 'extern' keyword to avoid multiple definition errors
extern bool stop_animation;
extern size_t total_test_count;  // Total tests to be run
extern size_t completed_tests;   // Tests completed so far
extern pthread_mutex_t progress_mutex; // For thread safety
extern char current_test_name[100];  // Current test being processed
extern bool force_complete; // New flag to force completion

#endif