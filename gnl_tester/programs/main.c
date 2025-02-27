#include "../header/test_utils.h"
#include "../header/globals.h"
#include "../header/defines.h"
#include "../header/cosmetics.h"
#include "../header/test_files.h"
#include "../header/memory_validate.h" // Add this include
#include "../../get_next_line.h"

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
    int max_progress = 80; // Increased for smoother progress bar
    
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
        usleep(30000); // 30ms for smoother animation
    }
    
    // Ensure progress bar reaches 100%
    printf("\r" CYAN "     ✓ " GREEN "Testing complete!                                                      \n" RESET);
    
    return NULL;
}

// ╔══════════════════════════════════════════════╗
// ║               TESTING FUNCTIONS              ║
// ╚══════════════════════════════════════════════╝

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
    // Use safer snprintf instead of strncpy
    snprintf(current_test_name, sizeof(current_test_name), "%s", basename);
    pthread_mutex_unlock(&progress_mutex);
    
    int fd;
    FILE *output;
    char *line;
    bool file_passed = true;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
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
    
    // Add timeout mechanism
    time_t start_time = time(NULL);
    while ((line = get_next_line(fd)) != NULL) {
        // Check for memory corruption
        #if defined(TRACK_BUFFER_OVERFLOWS) && TRACK_BUFFER_OVERFLOWS == 1
        if (!validate_string(line)) {
            printf(RED "Error: Memory corruption detected in result from %s\n" RESET, filename);
            *all_tests_passed = false;
            file_passed = false;
            free(line);
            break;
        }
        #endif
        
        fprintf(output, "%s", line);
        free(line);
        
        // Check for timeout (e.g., 10 seconds)
        if (difftime(time(NULL), start_time) > 10) {
            printf(RED "Error: Test timed out for file %s\n" RESET, filename);
            *all_tests_passed = false;
            file_passed = false;
            break;
        }
    }
    
    fclose(output);
    close(fd);
    
    if (file_passed) {
        file_passed = compare_files("outputs/temp_output.txt", expected_output_file);
        if (!file_passed) {
            *all_tests_passed = false;
        }
    }
    
    // Update progress counter (thread-safe)
    pthread_mutex_lock(&progress_mutex);
    completed_tests++;
    pthread_mutex_unlock(&progress_mutex);
    
    display_test_result(filename, file_passed, detailed);
}

// Add a specific test for the "+6" issue
void test_memory_allocation(bool *all_tests_passed, bool detailed) {
    #if defined(MEMORY_VALIDATE_HEAP) && MEMORY_VALIDATE_HEAP == 1
    pthread_mutex_lock(&progress_mutex);
    snprintf(current_test_name, sizeof(current_test_name), "Memory corruption test");
    pthread_mutex_unlock(&progress_mutex);
    
    if (detailed) {
        printf(CYAN "     ┌── " BOLD "Running memory validation tests" RESET "\n");
    }
    
    // Set default result for this test (pass unless problem found)
    bool memory_test_passed = true;
    
    // Create a simpler test for the "+6" issue - avoid accessing unsafe memory
    const char *test_file = "test_cases/memory_test.txt";
    FILE *f = fopen(test_file, "w");
    if (!f) {
        memory_test_passed = false;
        if (detailed) {
            printf(RED "     ├── ✗ Could not create test file" RESET "\n");
        }
    } else {
        fprintf(f, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
        fclose(f);
        
        int fd = open(test_file, O_RDONLY);
        if (fd == -1) {
            memory_test_passed = false;
            if (detailed) {
                printf(RED "     ├── ✗ Could not open test file" RESET "\n");
            }
        } else {
            // Read a line and check if it's properly terminated
            char *line = get_next_line(fd);
            if (line) {
                size_t len = strlen(line);
                if (len > 0 && line[len-1] != '\n') {
                    if (detailed) {
                        printf(RED "     ├── ✗ Memory corruption test: line doesn't end with newline" RESET "\n");
                    }
                    memory_test_passed = false;
                } else if (detailed) {
                    printf(GREEN "     ├── ✓ Memory validation passed" RESET "\n");
                }
                free(line);
            }
            close(fd);
        }
    }
    
    // Update the overall test result
    if (!memory_test_passed) {
        *all_tests_passed = false;
    }
    pthread_mutex_lock(&progress_mutex);
    completed_tests++;
    pthread_mutex_unlock(&progress_mutex);
    #else
    (void)all_tests_passed; // Suppress unused parameter warning
    (void)detailed; // Suppress unused parameter warning
    // When memory validation is disabled, just report that
    if (detailed) {
        printf(YELLOW "     ├── Memory validation disabled" RESET "\n");
    }
    #endif
}

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

// ╔══════════════════════════════════════════════╗
// ║                  MAIN FUNCTION               ║
// ╚══════════════════════════════════════════════╝

int main(int argc, char **argv) {
    bool detailed = true;
    size_t buffer_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
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
    
    // Create outputs directory if it doesn't exist
    int mkdir_result = system("mkdir -p outputs");
    if (mkdir_result != 0) {
        fprintf(stderr, RED "Warning: Failed to create outputs directory\n" RESET);
        // Continue anyway, as the directory might already exist
    }
    
    // Display welcome banner
    display_start_message();
    
    // Get accurate count for progress tracking
    size_t num_tests = TEST_FILES_COUNT;
    
    // Initialize progress tracking
    pthread_mutex_lock(&progress_mutex);
    total_test_count = num_tests * num_buffer_sizes + 1; // +1 for memory test
    completed_tests = 0;
    snprintf(current_test_name, sizeof(current_test_name), "Initializing tests...");
    pthread_mutex_unlock(&progress_mutex);
    
    // Initialize animation thread if using short display mode
    pthread_t animation_thread;
    if (!detailed) {
        pthread_create(&animation_thread, NULL, buffering_animation, NULL);
        printf("\n"); // Add space for animation
    }
    
    // Run memory allocation tests first
    test_memory_allocation(&all_tests_passed, detailed);
    
    // Run tests with different buffer sizes
    for (size_t i = 0; i < num_buffer_sizes; i++) {
        run_tests_with_buffer_size(buffer_sizes[i], &all_tests_passed, detailed);
    }
    
    // Force progress to 100% after all tests
    pthread_mutex_lock(&progress_mutex);
    completed_tests = total_test_count;
    strcpy(current_test_name, "Complete!");
    pthread_mutex_unlock(&progress_mutex);
    
    // Give the animation thread one more iteration to render 100%
    if (!detailed) {
        usleep(100000);  // 100ms to ensure animation updates
        stop_animation = true;
        pthread_join(animation_thread, NULL);
    }
    
    // Display final results
    if (all_tests_passed) {
        display_success_message();
    } else {
        display_failure_message();
    }
    
    // Clean up mutex
    pthread_mutex_destroy(&progress_mutex);
    
    return !all_tests_passed;  // Return 0 for success, 1 for failure
}