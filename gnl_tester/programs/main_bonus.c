#include "../header/test_utils.h"
#include "../header/defines.h"
#include "../header/globals.h"
#include "../header/cosmetics.h"
#include "../header/test_files.h"
#include "../header/gnl_wrapper.h"
#include "../../get_next_line_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define NUM_FILES 36

//void display_start_message() {
//
//   printf( BLUE" /$$$$$$$   /$$$$$$  /$$   /$$ /$$   /$$  /$$$$$$    " NEWLINE);
//   printf( "| $$__  $$ /$$__  $$| $$$ | $$| $$  | $$ /$$__  $$ " NEWLINE);
//   printf( "| $$  \\ $$| $$  \\ $$| $$$$| $$| $$  | $$| $$  \\__/ " NEWLINE);
//   printf( "| $$$$$$$ | $$  | $$| $$ $$ $$| $$  | $$|  $$$$$$  "NEWLINE);
//   printf( "| $$__  $$| $$  | $$| $$  $$$$| $$  | $$ \\____  $$ "NEWLINE);
//   printf( "| $$  \\ $$| $$  | $$| $$\\  $$$| $$  | $$ /$$  \\ $$ "NEWLINE);
//   printf( "| $$$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/|  $$$$$$/ "NEWLINE);
//   printf( "|_______/  \\______/ |__/  \\__/ \\______/  \\______/  "NEWLINE RESET);
//                                                      
//}
//
//void display_success_message() {
//    printf(YELLOW);
//    printf("\n");
//    printf("     ✨ All Tests Passed! ✨\n");
//    printf("\n");
//    printf("         .-=========-.       \n");
//    printf("         \\'-=======-'/       \n");
//    printf("         _|   .=.   |_       \n");
//    printf("        ((|"  GREEN"  {{1}}" YELLOW "  |))      \n");
//    printf("         \\|   /|\\   |/       \n");
//    printf("          \\__ '`' __/        \n");
//    printf("            _`) (`_          \n");
//    printf("          _/_______\\_        \n");
//    printf("         /___________\\       \n");
//    printf("\n");
//    printf("    🎉 Success Trophy 🎉     \n");
//    printf("\n");
//    printf(RESET);
//}
//
//void display_failure_message() {
//    printf("\033[1;31m");
//    printf("\n");
//    printf("     💥 Some Tests Failed! 💥\n");
//    printf("\n");
//    printf("         .-=========-.       \n");
//    printf("         \\'-=======-'/       \n");
//    printf("         _|   .=.   |_       \n");
//    printf("        ((|  {{1}}  |))      \n");
//    printf("         \\|   /|\\   |/       \n");
//    printf("          \\__ '`' __/        \n");
//    printf("            _`) (`_          \n");
//    printf("          _/_______\\_        \n");
//    printf("         /___________\\       \n");
//    printf("\n");
//    printf("    💔 Failure Trophy 💔     \n");
//    printf("\n");
//    printf("\033[0m");
//}

void test_file(const char *filename, const char *expected_output_file, bool *all_tests_passed, bool detailed)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        *all_tests_passed = false;
        if (detailed) printf("❌ Error opening file: %s\n", filename);
        return;
    }

    FILE *output = fopen("outputs/temp_output.txt", "w");
    if (!output) {
        close(fd);
        *all_tests_passed = false;
        if (detailed) printf("❌ Error opening output file\n");
        return;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        fprintf(output, "%s", line);
        free(line);
    }

    fclose(output);
    close(fd);

    if (compare_files("outputs/temp_output.txt", expected_output_file)) {
        if (detailed) {
            printf(GREEN "✅ %s matches %s\n" RESET, filename, expected_output_file);
        }
    } else {
        *all_tests_passed = false;
        if (detailed) {
            printf(RED "❌ %s does not match %s\n" RESET, filename, expected_output_file);
        }
    }
}

// Update function declaration to use proper C99 style with (void)
void test_multiple_fds(void)
{
    int fds[NUM_FILES];
    int total_tests = 0;
    int passed_tests = 0;
    int failed_tests = 0;

    printf("\n%s=== GET_NEXT_LINE BONUS TESTER ===%s\n", YELLOW, RESET);
    printf("Testing %d different files simultaneously\n\n", NUM_FILES);

    const char *filenames[NUM_FILES] = {
        "test_cases/empty", "test_cases/one_line.txt", "test_cases/multi_lines.txt",
        "test_cases/no_newline.txt", "test_cases/big_file.txt", "test_cases/1char.txt",
        "test_cases/41_no_nl", "test_cases/41_with_nl", "test_cases/42_no_nl",
        "test_cases/42_with_nl", "test_cases/43_with_nl", "test_cases/big_line_with_nl",
        "test_cases/giant_line.txt", "test_cases/lines_around_10.txt", "test_cases/multi_lines.txt",
        "test_cases/multiple_line_with_nl", "test_cases/multiple_nl.txt", "test_cases/multiple_nlx5",
        "test_cases/nl", "test_cases/no_newline.txt", "test_cases/one_line_no_nl.txt",
        "test_cases/one_line.txt", "test_cases/only_nl.txt", "test_cases/variable_nls.txt",
        "test_cases/1-brouette.txt", "test_cases/2-otarie.txt", "test_cases/3-oneline.txt",
        "test_cases/4-u.txt", "test_cases/5-empty.txt", "test_cases/6-newline.txt",
        "test_cases/7-onechar.txt", "test_cases/8-twochar.txt", "test_cases/9-linew.txt",
        "test_cases/10-b.txt", "test_cases/11-bg.txt", "test_cases/12-bigben.txt"
    };

    const char *expected_outputs[NUM_FILES] = {
        "expected_output/empty", "expected_output/one_line.txt", "expected_output/multi_lines.txt",
        "expected_output/no_newline.txt", "expected_output/big_file.txt", "expected_output/1char.txt",
        "expected_output/41_no_nl", "expected_output/41_with_nl", "expected_output/42_no_nl",
        "expected_output/42_with_nl", "expected_output/43_with_nl", "expected_output/big_line_with_nl",
        "expected_output/giant_line.txt", "expected_output/lines_around_10.txt", "expected_output/multi_lines.txt",
        "expected_output/multiple_line_with_nl", "expected_output/multiple_nl.txt", "expected_output/multiple_nlx5",
        "expected_output/nl", "expected_output/no_newline.txt", "expected_output/one_line_no_nl.txt",
        "expected_output/one_line.txt", "expected_output/only_nl.txt", "expected_output/variable_nls.txt",
        "expected_output/1-brouette.txt", "expected_output/2-otarie.txt", "expected_output/3-oneline.txt",
        "expected_output/4-u.txt", "expected_output/5-empty.txt", "expected_output/6-newline.txt",
        "expected_output/7-onechar.txt", "expected_output/8-twochar.txt", "expected_output/9-linew.txt",
        "expected_output/10-b.txt", "expected_output/11-bg.txt", "expected_output/12-bigben.txt"
    };

    // Open all test files and count successful opens
    printf("%s>>> Opening files...%s\n", YELLOW, RESET);
    int successfully_opened = 0;
    for (int i = 0; i < NUM_FILES; i++)
    {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1)
        {
            printf("%s❌ Failed to open: %s%s\n", RED, filenames[i], RESET);
        }
        else
        {
            successfully_opened++;
            printf("%s✓ Opened: %s%s\n", GREEN, filenames[i], RESET);
        }
    }

    if (successfully_opened == 0)
    {
        printf("%s❌ No files could be opened. Aborting tests.%s\n", RED, RESET);
        return;
    }

    printf("\n%s>>> Starting tests with %d files...%s\n", YELLOW, successfully_opened, RESET);
    int active_fds = successfully_opened;
    char *line;
    int line_number[NUM_FILES] = {0};

    // Read from all FDs in a round-robin fashion
    while (active_fds > 0)
    {
        for (int i = 0; i < NUM_FILES; i++)
        {
            if (fds[i] == -1) continue;

            line = get_next_line(fds[i]);
            total_tests++;

            if (line)
            {
                printf("\n%s=== Testing FD %d (File: %s) ===%s\n", YELLOW, fds[i], filenames[i], RESET);
                printf("Line content: %s", line);

                // Compare with expected output
                FILE *expected = fopen(expected_outputs[i], "r");
                if (!expected) {
                    printf("%s❌ Error: Could not open expected output file: %s%s\n", RED, expected_outputs[i], RESET);
                    free(line);
                    continue;
                }

                char expected_line[4096];
                for (int j = 0; j <= line_number[i]; j++) {
                    if (fgets(expected_line, sizeof(expected_line), expected) == NULL) {
                        break;
                    }
                }

                // Remove newline character from expected_line if present
                size_t len = strlen(expected_line);
                if (len > 0 && expected_line[len - 1] == '\n') {
                    expected_line[len - 1] = '\0';
                }

                if (strcmp(line, expected_line) == 0) {
                    printf("%s✅ Line matches expected output%s\n", GREEN, RESET);
                    passed_tests++;
                } else {
                    printf("%s❌ Line mismatch%s\n", RED, RESET);
                    printf("Expected: %s\n", expected_line);
                    printf("Got     : %s\n", line);
                    failed_tests++;
                }

                fclose(expected);
                free(line);
                line_number[i]++;
            }
            else
            {
                printf("%s📁 Finished reading file: %s%s\n", YELLOW, filenames[i], RESET);
                close(fds[i]);
                fds[i] = -1;
                active_fds--;
            }
        }
    }

    // Print final statistics
    printf("\n%s=== Test Summary ===%s\n", YELLOW, RESET);
    printf("Total tests run: %d\n", total_tests);
    printf("%sTests passed  : %d%s\n", GREEN, passed_tests, RESET);
    printf("%sTests failed  : %d%s\n", RED, failed_tests, RESET);
    printf("Success rate  : %.2lf%%\n", (total_tests > 0) ? (double)passed_tests / total_tests * 100 : 0);
}

void run_tests_with_buffer_size(size_t buffer_size, bool *all_tests_passed, bool detailed)
{
    if (detailed) printf("\nRunning tests with BUFFER_SIZE = %zu\n", buffer_size);
    const char *test_files[][2] = {
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/one_line.txt", "expected_output/one_line.txt"},
        {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
        {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
        {"test_cases/big_file.txt", "expected_output/big_file.txt"},
        {"test_cases/1char.txt", "expected_output/1char.txt"},
        {"test_cases/41_no_nl", "expected_output/41_no_nl"},
        {"test_cases/41_no_nl copy 2", "expected_output/41_no_nl copy 2"},
        {"test_cases/41_with_nl", "expected_output/41_with_nl"},
        {"test_cases/42_no_nl", "expected_output/42_no_nl"},
        {"test_cases/42_with_nl", "expected_output/42_with_nl"},
        {"test_cases/43_no_nl", "expected_output/43_no_nl"},
        {"test_cases/43_with_nl", "expected_output/43_with_nl"},
        {"test_cases/big_line_with_nl", "expected_output/big_line_with_nl"},
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/giant_line.txt", "expected_output/giant_line.txt"},
        {"test_cases/lines_around_10.txt", "expected_output/lines_around_10.txt"},
        {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
        {"test_cases/multiple_line_no_nl", "expected_output/multiple_line_no_nl"},
        {"test_cases/multiple_line_with_nl", "expected_output/multiple_line_with_nl"},
        {"test_cases/multiple_nl.txt", "expected_output/multiple_nl.txt"},
        {"test_cases/multiple_nlx5", "expected_output/multiple_nlx5"},
        {"test_cases/nl", "expected_output/nl"},
        {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
        {"test_cases/one_line_no_nl.txt", "expected_output/one_line_no_nl.txt"},
        {"test_cases/one_line.txt", "expected_output/one_line.txt"},
        {"test_cases/only_nl.txt", "expected_output/only_nl.txt"},
        {"test_cases/variable_nls.txt", "expected_output/variable_nls.txt"},
        {"test_cases/1-brouette.txt", "expected_output/1-brouette.txt"},
        {"test_cases/2-otarie.txt", "expected_output/2-otarie.txt"},
        {"test_cases/3-oneline.txt", "expected_output/3-oneline.txt"},
        {"test_cases/4-u.txt", "expected_output/4-u.txt"},
        {"test_cases/5-empty.txt", "expected_output/5-empty.txt"},
        {"test_cases/6-newline.txt", "expected_output/6-newline.txt"},
        {"test_cases/7-onechar.txt", "expected_output/7-onechar.txt"},
        {"test_cases/8-twochar.txt", "expected_output/8-twochar.txt"},
        {"test_cases/9-linew.txt", "expected_output/9-linew.txt"},
        {"test_cases/10-b.txt", "expected_output/10-b.txt"},
        {"test_cases/11-bg.txt", "expected_output/11-bg.txt"},
        {"test_cases/12-bigben.txt", "expected_output/12-bigben.txt"},
    };

    size_t num_tests = sizeof(test_files) / sizeof(test_files[0]);

    for (size_t i = 0; i < num_tests; i++) {
        test_file(test_files[i][0], test_files[i][1], all_tests_passed, detailed);
    }
}

// Update main function to use command-line arguments instead of scanf
int main(int argc, char **argv)
{
    printf("DEBUG: Starting bonus tester...\n");
    bool detailed = true;
    
    // Parse command line arguments
    if (argc != 2) {
        printf(RED "Usage: %s [detailed/short]" RESET "\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "short") == 0) {
        detailed = false;
        printf("DEBUG: Running in short mode\n");
    } else if (strcmp(argv[1], "detailed") == 0) {
        detailed = true;
        printf("DEBUG: Running in detailed mode\n");
    } else {
        printf(RED "Invalid option: %s. Use 'detailed' or 'short'" RESET "\n", argv[1]);
        return 1;
    }
    
    printf("DEBUG: Creating test directories...\n");
    system("mkdir -p test_cases expected_output outputs");
    
    printf("DEBUG: About to display start message...\n");
    display_start_message();
    printf("DEBUG: Start message displayed!\n");

    size_t buffer_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
    size_t num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    bool all_tests_passed = true;

    printf("DEBUG: Creating simple test file...\n");
    FILE *test_file = fopen("test_cases/simple_test.txt", "w");
    if (test_file) {
        fprintf(test_file, "Line 1\nLine 2\nLine 3\n");
        fclose(test_file);
        printf("DEBUG: Test file created successfully\n");
        
        FILE *expected_file = fopen("expected_output/simple_test.txt", "w");
        if (expected_file) {
            fprintf(expected_file, "Line 1\nLine 2\nLine 3\n");
            fclose(expected_file);
            printf("DEBUG: Expected output file created\n");
        }
    }

    printf("DEBUG: Running tests with buffer size 42...\n");
    // Just run one buffer size for initial testing
    run_tests_with_buffer_size(42, &all_tests_passed, detailed);
    
    printf("DEBUG: Tests completed. Display results...\n");
    if (all_tests_passed) {
        display_success_message();
    } else {
        display_failure_message();
    }
    
    printf("DEBUG: Tester completed!\n");
    return 0;
}
