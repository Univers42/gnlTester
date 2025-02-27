#include "../header/test_utils.h"
#include "../header/cosmetics.h"
#include <unistd.h>  // For usleep()

 void display_success_message(void) {
    printf("\n");
    printf(GREEN "     ╔═══════════════════════════════════════════════╗\n" RESET);
    printf(GREEN "     ║           " BLINK "✅ ALL TESTS PASSED! ✅" RESET GREEN "           ║\n" RESET);
    printf(GREEN "     ╚═══════════════════════════════════════════════╝\n\n" RESET);
    
    printf(YELLOW "           .-=========-.\n" RESET);
    printf(YELLOW "           \\'-=======-'/\n" RESET);
    printf(YELLOW "           _|   .=.   |_\n" RESET);
    printf(YELLOW "          ((|  {{1}}  |))\n" RESET);
    printf(YELLOW "           \\|   /|\\   |/\n" RESET);
    printf(YELLOW "            \\__ '`' __/\n" RESET);
    printf(YELLOW "              _`) (`_\n" RESET);
    printf(GREEN "            _/_______\\_\n" RESET);
    printf(GREEN "           /___________\\\n\n" RESET);
    
    printf(CYAN "     🎯 " BOLD "Performance Metrics:" RESET "\n");
    printf(CYAN "     ├──" RESET " Memory Usage: " GREEN "Optimal" RESET "\n");
    printf(CYAN "     ├──" RESET " Speed: " GREEN "Excellent" RESET "\n");
    printf(CYAN "     └──" RESET " Code Quality: " GREEN "Outstanding" RESET "\n\n");
    
    printf(YELLOW "     🏆 " BOLD "CONGRATULATIONS!" RESET YELLOW " Your GNL implementation is solid! 🏆\n\n" RESET);
}

void display_failure_message(void) {
    printf("\n");
    printf(RED "     ╔═══════════════════════════════════════════════╗\n" RESET);
    printf(RED "     ║           " BLINK "❌ SOME TESTS FAILED! ❌" RESET RED "           ║\n" RESET);
    printf(RED "     ╚═══════════════════════════════════════════════╝\n\n" RESET);
    
    printf(RED "           .-=========-.\n" RESET);
    printf(RED "           \\'-=======-'/\n" RESET);
    printf(RED "           _|   .=.   |_\n" RESET);
    printf(RED "          ((|  {{1}}  |))\n" RESET);
    printf(RED "           \\|   /|\\   |/\n" RESET);
    printf(RED "            \\__ '`' __/\n" RESET);
    printf(RED "              _`) (`_\n" RESET);
    printf(RED "            _/_______\\_\n" RESET);
    printf(RED "           /___________\\\n\n" RESET);
    
    printf(YELLOW "     🔍 " BOLD "Debugging Tips:" RESET "\n");
    printf(YELLOW "     ├──" RESET " Check buffer handling in edge cases\n");
    printf(YELLOW "     ├──" RESET " Verify memory allocation and freeing\n");
    printf(YELLOW "     └──" RESET " Look for issues with newline detection\n\n");
    
    printf(CYAN "     💪 " BOLD "DON'T GIVE UP!" RESET CYAN " Debugging is part of the learning process!\n\n" RESET);
}

 void display_start_message(void) {
    printf(CLEAR_SCREEN);
    printf("\n");
    printf(CYBER1 "     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n" RESET);
    printf(CYBER2 "     ┃  " BOLD "GET_NEXT_LINE" RESET CYBER2 " - ULTIMATE TEST SUITE                     ┃\n" RESET);
    printf(CYBER3 "     ┃  " RESET YELLOW "Version 2.0" RESET CYBER3 "                                           ┃\n" RESET);
    printf(CYBER4 "     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n" RESET);
    
    printf(MAGENTA "     ╭────────────────────────────────────────────────────╮\n" RESET);
    printf(MAGENTA "     │" RESET);
    printf(BLUE "  ██████╗ ███╗   ██╗██╗         ████████╗███████╗███████╗████████╗ " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     │" RESET);
    printf(CYAN " ██╔════╝ ████╗  ██║██║         ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝ " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     │" RESET);
    printf(GREEN " ██║  ███╗██╔██╗ ██║██║            ██║   █████╗  ███████╗   ██║    " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     │" RESET);
    printf(YELLOW " ██║   ██║██║╚██╗██║██║            ██║   ██╔══╝  ╚════██║   ██║    " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     │" RESET);
    printf(RED " ╚██████╔╝██║ ╚████║███████╗       ██║   ███████╗███████║   ██║    " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     │" RESET);
    printf(CYBER1 "  ╚═════╝ ╚═╝  ╚═══╝╚══════╝       ╚═╝   ╚══════╝╚══════╝   ╚═╝    " RESET);
    printf(MAGENTA "│\n" RESET);
    
    printf(MAGENTA "     ╰────────────────────────────────────────────────────╯\n\n" RESET);
    
    printf(CYBER2 "     📋 Testing your get_next_line implementation...\n" RESET);
    printf(CYBER3 "     🛠️  Checking various edge cases and file formats...\n" RESET);
    printf(CYBER4 "     ⚡ Running high-performance validations...\n\n" RESET);
    
    fflush(stdout);
    usleep(800000); // 0.8 seconds pause for dramatic effect - CHANGED FROM sleep() TO usleep()
}

void display_test_header(size_t buffer_size) {
    printf("\n");
    printf(CYAN "     ╭──────────────────────────────────────────────────╮\n" RESET);
    printf(CYAN "     │  " BOLD "Testing with BUFFER_SIZE = %-6zu" RESET CYAN "               │\n" RESET, buffer_size);
    printf(CYAN "     ╰──────────────────────────────────────────────────╯\n\n" RESET);
}


void display_test_result(const char *filename, bool success, bool detailed) {
    if (!detailed) return;
    
    char short_name[30];
    const char *basename = strrchr(filename, '/');
    basename = basename ? basename + 1 : filename;
    
    // Truncate long filenames for display
    if (basename) {
        snprintf(short_name, 29, "%s", basename);
        if (strlen(basename) > 28) {
            short_name[25] = '.';
            short_name[26] = '.';
            short_name[27] = '.';
            short_name[28] = '\0';
        }
    } else {
        snprintf(short_name, 29, "unknown");
    }
    
    if (success) {
        printf(CYAN "     ├── " GREEN "✓ %-30s" RESET " " GREEN "PASS" RESET "\n", short_name);
    } else {
        printf(CYAN "     ├── " RED "✗ %-30s" RESET " " RED "FAIL" RESET "\n", short_name);
    }
}
