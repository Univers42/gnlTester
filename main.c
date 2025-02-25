#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include "../get_next_line.h"
#include "test_utils.h"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define WHITE "\033[1;37m"
#define new_line "\n"
void display_start_message() {
    printf(YELLOW"_   .-')       ('-.          .-') _   _ .-') _      ('-.      .-') _                  _  .-')                 "new_line);
    printf(CYAN"( '.( OO )_    ( OO ).-.     ( OO ) ) ( (  OO) )    ( OO ).-. (  OO) )                ( \\( -O )                "new_line);
    printf(" ,--.   ,--.)  / . --. / ,--./ ,--,'   \\     .'_    / . --. / /     '._   .-'),-----.  ,------.    ,--.   ,--."new_line);
    printf(" |   `.'   |   | \\-.  \\  |   \\ |  |\\   ,`'--..._)   | \\-.  \\  |'--...__) ( OO'  .-.  ' |   /`. '    \\  `.'  / "new_line);
    printf(" |         | .-'-'  |  | |    \\|  | )  |  |  \\  ' .-'-'  |  | '--.  .--' /   |  | |  | |  /  | |  .-')     /  "new_line);
    printf(" |  |'.'|  |  \\| |_.'  | |  .     |/   |  |   ' |  \\| |_.'  |    |  |    \\_) |  |\\|  | |  |_.' | (OO  \\   /   "new_line);
    printf(" |  |   |  |   |  .-.  | |  |\\    |    |  |   / :   |  .-.  |    |  |      \\ |  | |  | |  .  '.'  |   /  /\\_  "new_line);
    printf(" |  |   |  |   |  | |  | |  | \\   |    |  '--'  /   |  | |  |    |  |       `'  '-'  ' |  |\\  \\   `-./  /.__) "new_line);
    printf(BLUE" `--'   `--'   `--' `--' `--'  `--'    `-------'    `--' `--'    `--'         `-----'  `--' '--'    `--'      "new_line RESET);
}

void display_success_message() {
    printf(YELLOW); // Set text color to green
    printf("\n");
    printf("     ✨ All Tests Passed! ✨\n");
    printf("\n");
    printf("         .-=========-.       \n");
    printf("         \\'-=======-'/       \n");
    printf("         _|   .=.   |_       \n");
    printf(GREEN"        ((|  {{1}}  |))      \n");
    printf(YELLOW"         \\|   /|\\   |/       \n");
    printf("          \\__ '`' __/        \n");
    printf("            _`) (`_          \n");
    printf("          _/_______\\_        \n");
    printf("         /___________\\       \n");
    printf("\n");
    printf("    🎉 Success Trophy 🎉     \n");
    printf("\n");
    printf("\033[0m"); // Reset text color
}

void display_failure_message() {
    printf("\033[1;31m"); // Set text color to red
    printf("\n");
    printf("     💥 Some Tests Failed! 💥\n");
    printf("\n");
    printf("         .-=========-.       \n");
    printf("         \\'-=======-'/       \n");
    printf("         _|   .=.   |_       \n");
    printf("        ((|  {{1}}  |))      \n");
    printf("         \\|   /|\\   |/       \n");
    printf("          \\__ '`' __/        \n");
    printf("            _`) (`_          \n");
    printf("          _/_______\\_        \n");
    printf("         /___________\\       \n");
    printf("\n");
    printf("    💔 Failure Trophy 💔     \n");
    printf("\n");
    printf("\033[0m"); // Reset text color
}

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
    if (!output)
    {
        close(fd);
        *all_tests_passed = false;
        if (detailed) printf("❌ Error opening output file\n");
        return;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        fprintf(output, "%s", line); // Remove the extra newline character
        free(line);
    }
    fclose(output);
    close(fd);

    if (compare_files("outputs/temp_output.txt", expected_output_file))
    {
        if (detailed) 
            printf("✅ %s matches %s\n", filename, expected_output_file);
    } 
    else 
    {
        *all_tests_passed = false;
        if (detailed)
            printf("❌ %s does not match %s\n", filename, expected_output_file);
    }
}

void run_tests_with_buffer_size(size_t buffer_size, bool *all_tests_passed, bool detailed)
{
    if (detailed)
        printf("\nRunning tests with BUFFER_SIZE = %zu\n", buffer_size);
    const char *test_files[][2] = {
        {"test_cases/empty.txt", "expected_output/empty.txt"},
        {"test_cases/one_line.txt", "expected_output/one_line.txt"},
        {"test_cases/multi_lines.txt", "expected_output/multi_lines.txt"},
        {"test_cases/no_newline.txt", "expected_output/no_newline.txt"},
        {"test_cases/big_file.txt", "expected_output/big_file.txt"},
        {"test_cases/1char.txt", "expected_output/1char.txt"},
        {"test_cases/41_no_nl", "expected_output/41_no_nl"},
        {"test_cases/41_no_nl copy 2", "expected_output/41_no_nl copy 2"},
        //{"test_cases/41_no_nl copy3", "expected_output/41_no_nl copy3"},
        {"test_cases/41_with_nl", "expected_output/41_with_nl"},
        {"test_cases/42_no_nl", "expected_output/42_no_nl"},
        {"test_cases/42_with_nl", "expected_output/42_with_nl"},
        {"test_cases/43_no_nl", "expected_output/43_no_nl"},
        //{"test_cases/43_no_nl_copy", "expected_output/43_no_nl_copy"},
        {"test_cases/43_with_nl", "expected_output/43_with_nl"},
        //{"test_cases/alternate_line_nl_no_nl", "expected_output/alternate_line_nl_no_nl"},
        //{"test_cases/alternate_line_with_nl", "expected_output/alternate_line_with_nl"},
        //{"test_cases/big_line_no_nl.txt", "expected_output/big_line_no_nl.txt"},
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
    for (size_t i = 0; i < num_tests; i++)
        test_file(test_files[i][0], test_files[i][1], all_tests_passed, detailed);
}

#define CYBER1  "\033[38;5;45m"  // Electric Blue
#define CYBER2  "\033[38;5;201m" // Neon Pink
#define CYBER3  "\033[38;5;47m"  // Toxic Green
#define CYBER4  "\033[38;5;220m" // Holographic Yellow
#define CLEAR_SCREEN "\033[H\033[J"

bool stop_animation = false;

void *buffering_animation() {
    const char *frames[][2] = {
        {BLUE   "  ◢█◣  \n ◢████◣ \n◢██████◣\n◥██████◤\n ◥████◤ \n  ◥█◤  " RESET, "Booting up..."},
        {CYAN   "  ◢█◣  \n ◢██◤█◣ \n◢██◤◢██◣\n◥██◣◥██◤\n ◥█◣█◤ \n  ◥█◤  " RESET, "Calibrating systems..."},
        {GREEN  "  ◢█◣  \n ◢█◤◢█◣ \n◢█◤◢███◣\n◥█◣◥███◤\n ◥█◣◥█◤ \n  ◥█◤  " RESET, "Processing requests..."},
        {MAGENTA "  ◢█◣  \n ◢◤◢██◣ \n◢◤◢████◣\n◥◣◥████◤\n ◥◣◥██◤ \n  ◥█◤  " RESET, "Finalizing..."},
        {YELLOW "  ◢█◣  \n ◢████◣ \n◢██████◣\n◥██████◤\n ◥████◤ \n  ◥█◤  " RESET, "Almost there..."},
        {RED    "  ◢█◣  \n ◢████◣ \n◢██████◣\n◥██████◤\n ◥████◤ \n  ◥█◤  " RESET, "COMPLETE! 🚀"},
    };

    int num_frames = sizeof(frames) / sizeof(frames[0]);
    int i = 0;

    while (!stop_animation) {
        printf("\033[H\033[J");  // Clear screen
        printf("\033[1;1H");     // Move cursor to top-left
        printf("%s\n%s\n", frames[i % num_frames][0], frames[i % num_frames][1]);
        fflush(stdout);
        i++;
        usleep(200000);  // Sleep for 200ms
    }

    printf("\033[H\033[J");  // Clear screen after animation ends
    printf(GREEN "✔ Process Completed Successfully!\n" RESET);
    return NULL;
}

// Start animation in a separate thread
void start_animation() {
    pthread_t animation_thread;
    pthread_create(&animation_thread, NULL, buffering_animation, NULL);
}

// Stop animation
void stop_animation_func() {
    stop_animation = true;
}

int main(int argc, char **argv)
{
    char choice[10];
    bool detailed = true;
    size_t buffer_sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
    size_t num_buffer_sizes;
    bool all_tests_passed;

    if(argc != 2)
    {
        fprintf(stderr, "./usage [detailed/short]");
        return (1);
    }
    strcpy(choice, argv[1]);
    //printf("Choose output type (detailed/short): ");
    //scanf("%9s", choice);
    if (strcmp(choice, "short") == 0)
        detailed = false;
    else if(strcmp(choice, "detailed") == 0)
        detailed = true;
    else
        return (fprintf(stderr, "./usage [detailed/short]"), 1);
    display_start_message();
    num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    all_tests_passed = true;

    pthread_t animation_thread;
    if (!detailed) {
        pthread_create(&animation_thread, NULL, buffering_animation, NULL);
    }

    for (size_t i = 0; i < num_buffer_sizes; i++)
        run_tests_with_buffer_size(buffer_sizes[i], &all_tests_passed, detailed);

    if (!detailed) {
        stop_animation = true;
        pthread_join(animation_thread, NULL);
    }

    if (all_tests_passed)
        display_success_message();
    else
        display_failure_message();
    return 0;
}