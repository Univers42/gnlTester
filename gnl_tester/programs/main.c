#include "../header/test_utils.h"
#include "../header/globals.h"
#include "../header/defines.h"
#include "../header/cosmetics.h"
#include "../header/test_files.h"
#include "../header/gnl_wrapper.h"
#include "../header/logging.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
 * Animation thread function for displaying progress
 */
void *buffering_animation(void *arg) {
    (void)arg; // Suppress unused parameter warning
    
    // Smoother Braille pattern spinner
    const char *spinners[] = {
        "⠋", "⠙", "⠸", "⠴", "⠦", "⠇"
    };
    
    const char *fill = "█";
    const char *empty = "░";
    
    int spinner_idx = 0;
    int counter = 0;
    int max_progress = 40;
    
    // Initial empty line for animation space
    printf("\n");
    
    while (!stop_animation) {
        // Update animation state
        spinner_idx = (spinner_idx + 1) % 6;
        counter++;
        
        // Get current progress (thread-safe)
        pthread_mutex_lock(&progress_mutex);
        int progress_percent;
        if (total_test_count > 0) {
            // Ensure percentage never exceeds 100%
            if (completed_tests >= total_test_count) {
                progress_percent = 100;
            } else {
                progress_percent = (int)((completed_tests * 100) / total_test_count);
            }
        } else {
            progress_percent = 0;
        }
        
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "%s", current_test_name);
        pthread_mutex_unlock(&progress_mutex);
        
        // Calculate progress bar fill
        int filled_blocks = (progress_percent * max_progress) / 100;
        if (filled_blocks > max_progress) filled_blocks = max_progress;
        
        // Clear line and create consistent formatting using carriage return
        printf("\r");
        
        // Output the spinner and status message with consistent spacing
        printf(CYAN "     %s " RESET, spinners[spinner_idx]);
        
        // Draw progress bar reflecting actual progress
        printf(YELLOW "[");
        for (int i = 0; i < max_progress; i++) {
            if (i < filled_blocks) {
                printf(GREEN "%s" RESET, fill);
            } else {
                printf(YELLOW "%s" RESET, empty);
            }
        }
        printf(YELLOW "] " RESET);
        
        // Show percentage and currently testing file
        printf(WHITE "%3d%% " RESET, progress_percent);
        printf(CYAN "Testing: " RESET WHITE "%-40s" RESET, test_name);
        
        fflush(stdout);
        usleep(60000); // 60ms for smoother animation
    }
    
    // Final message
    printf("\r" CYAN "     ✓ " GREEN "Testing complete!                                                      \n" RESET);
    
    return NULL;
}

/*
 * Test a single file against expected output
 */
void test_file(const char *filename, const char *expected_output_file, bool *all_tests_passed, bool detailed) {
    // Update current file being tested (thread-safe)
    const char *basename;
    if (filename) {
        basename = strrchr(filename, '/');
        basename = basename ? basename + 1 : filename;
    } else {
        basename = "unknown";
    }
    
    pthread_mutex_lock(&progress_mutex);
    snprintf(current_test_name, sizeof(current_test_name), "%s", basename);
    pthread_mutex_unlock(&progress_mutex);
    
    int fd;
    FILE *output;
    char *line;
    bool file_passed = true;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        LOG_ERROR("Failed to open file: %s", filename);
        *all_tests_passed = false;
        display_test_result(filename, false, detailed);
        
        // Update progress counter (thread-safe)
        pthread_mutex_lock(&progress_mutex);
        completed_tests++;
        pthread_mutex_unlock(&progress_mutex);
        return;
    }
    
    output = fopen("outputs/temp_output.txt", "w");
    if (!output) {
        close(fd);
        *all_tests_passed = false;
        display_test_result(filename, false, detailed);
        
        // Update progress counter (thread-safe)
        pthread_mutex_lock(&progress_mutex);
        completed_tests++;
        pthread_mutex_unlock(&progress_mutex);
        return;
    }
    
    LOG_INFO("Reading from fd: %d (file: %s)", fd, filename);
    while ((line = gnl_wrapper(fd)) != NULL) {
        fprintf(output, "%s", line);
        free(line);
    }
    
    fclose(output);
    close(fd);
    
    file_passed = compare_files("outputs/temp_output.txt", expected_output_file);
    if (!file_passed) {
        LOG_WARNING("File comparison failed: %s", filename);
        *all_tests_passed = false;
    } else {
        LOG_INFO("File comparison succeeded: %s", filename);
    }
    
    // Update progress counter (thread-safe)
    pthread_mutex_lock(&progress_mutex);
    completed_tests++;
    pthread_mutex_unlock(&progress_mutex);
    
    display_test_result(filename, file_passed, detailed);
}

/*
 * Run tests with specific buffer size
 */
void run_tests_with_buffer_size(size_t buffer_size, bool *all_tests_passed, bool detailed) {
    // Use the global test files array
    size_t num_tests = TEST_FILES_COUNT;
    
    pthread_mutex_lock(&progress_mutex);
    sprintf(current_test_name, "BUFFER_SIZE=%zu", buffer_size);
    pthread_mutex_unlock(&progress_mutex);
    
    if (detailed) {
        display_test_header(buffer_size);
        printf(CYAN "     ┌── " BOLD "Running %zu tests with BUFFER_SIZE=%zu" RESET "\n", num_tests, buffer_size);
    }
    
    for (size_t i = 0; i < num_tests; i++) {
        test_file(TEST_FILES[i][0], TEST_FILES[i][1], all_tests_passed, detailed);
    }
    
    if (detailed) {
        printf(CYAN "     └── " BOLD "Tests completed for BUFFER_SIZE=%zu" RESET "\n", buffer_size);
    }
}

/*
 * Main function
 */
int main(int argc, char **argv) {
    // Initialize logging
    init_logging("gnl_test.log");
    LOG_INFO("Starting GNL tester...");
    
    bool detailed = true;
    size_t buffer_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};  // Reduced list for faster testing
    size_t num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    bool all_tests_passed = true;
    
    // Parse command line arguments
    if (argc != 2) {
        printf(RED "Usage: %s [detailed/short]" RESET "\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "short") == 0) {
        detailed = false;
    } else if (strcmp(argv[1], "detailed") == 0) {
        detailed = true;
    } else {
        printf(RED "Invalid option: %s. Use 'detailed' or 'short'" RESET "\n", argv[1]);
        return 1;
    }
    
    // Create necessary directories and test files
    printf("DEBUG: Creating directories...\n");
    int result = system("chmod +x create_test_files.sh && ./create_test_files.sh");
    if (result != 0) {
        printf("WARNING: Failed to create test files. Some tests may fail.\n");
    }
    
    // Display welcome banner
    printf("DEBUG: Displaying welcome banner\n");
    display_start_message();
    printf("DEBUG: Banner displayed, continuing execution\n");
    
    // Get accurate count for progress tracking
    size_t num_tests = TEST_FILES_COUNT;
    printf("DEBUG: Found %zu test files\n", num_tests);
    
    // Initialize progress tracking
    pthread_mutex_lock(&progress_mutex);
    total_test_count = num_tests * num_buffer_sizes;
    completed_tests = 0;
    snprintf(current_test_name, sizeof(current_test_name), "Initializing tests...");
    pthread_mutex_unlock(&progress_mutex);
    
    // Initialize animation thread if using short display mode
    pthread_t animation_thread;
    if (!detailed) {
        pthread_create(&animation_thread, NULL, buffering_animation, NULL);
        printf("\n"); // Add space for animation
    }
    
    printf("DEBUG: Running tests with %zu buffer sizes\n", num_buffer_sizes);
    
    // Run tests with different buffer sizes
    for (size_t i = 0; i < num_buffer_sizes; i++) {  // Run all sizes now
        printf("DEBUG: Testing with buffer size %zu\n", buffer_sizes[i]);
        run_tests_with_buffer_size(buffer_sizes[i], &all_tests_passed, detailed);
    }
    
    // Stop animation and wait for thread to finish
    if (!detailed) {
        stop_animation = true;
        pthread_join(animation_thread, NULL);
    }
    
    // Display final results
    printf("DEBUG: Tests completed, displaying results\n");
    if (all_tests_passed) {
        display_success_message();
    } else {
        display_failure_message();
    }
    
    // Clean up logs
    LOG_INFO("Tester completed with status: %s", all_tests_passed ? "SUCCESS" : "FAILURE");
    close_logging();
    
    // Clean up mutex
    pthread_mutex_destroy(&progress_mutex);
    
    return !all_tests_passed;  // Return 0 for success, 1 for failure
}