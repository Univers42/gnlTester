#include "../header/globals.h"

// Global variable definitions
bool stop_animation = false;
size_t total_test_count = 0;
size_t completed_tests = 0;
pthread_mutex_t progress_mutex = PTHREAD_MUTEX_INITIALIZER;
char current_test_name[100] = "Initializing...";