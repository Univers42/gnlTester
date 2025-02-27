/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmetics_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:40 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:54:18 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/test_utils.h"
#include "../header/cosmetics.h"
#include <unistd.h>
void display_success_message(void) {
    printf("\n");
    printf(GREEN "     ╔═════════════════════════════════════════════════════════════╗\n" RESET);
    printf(GREEN "     ║               " BLINK "✅ ALL TESTS PASSED! ✅" RESET GREEN "                       ║\n" RESET);
    printf(GREEN "     ╚═════════════════════════════════════════════════════════════╝\n\n" RESET);
    //
    //printf(YELLOW "            .-=========-.             \n" RESET);
    //printf(GOLD "           \\\\-'         '-//          \n" RESET);
    //printf(GOLD "            |" SILVER " ####     #### " GOLD "|           \n" RESET);
    //printf(GOLD "            |" SILVER " ####     #### " GOLD "|           \n" RESET);
    //printf(GOLD "            |" SILVER " ####     #### " GOLD "|           \n" RESET);
    //printf(GOLD "            \\" SILVER " ####     #### " GOLD "/           \n" RESET);
    //printf(GOLD "             \\" SILVER " ###     ### " GOLD "/            \n" RESET);
    //printf(GOLD "              \\'" SILVER " #     # " GOLD "'/             \n" RESET);
    //printf(GOLD "               \\" SILVER "  #####  " GOLD "/              \n" RESET);
    //printf(GOLD "               |" SILVER " ####### " GOLD "|              \n" RESET);
    //printf(GOLD "               |" YELLOW " ####### " GOLD "|              \n" RESET);
    //printf(GOLD "               |" YELLOW " ####### " GOLD "|              \n" RESET);
    //printf(GOLD "               |" YELLOW " ####### " GOLD "|              \n" RESET);
    //printf(GOLD "              /|" YELLOW " ####### " GOLD "|\\             \n" RESET);
    //printf(GOLD "             / |" YELLOW " ####### " GOLD "| \\            \n" RESET);
    //printf(GOLD "            /  |" YELLOW " ####### " GOLD "|  \\           \n" RESET);
    //printf(GOLD "           |=====" YELLOW " ####### " GOLD "=====|          \n" RESET);
    //printf(GOLD "            \\____|" YELLOW " ### " GOLD "|____/           \n" RESET);
    //printf(GOLD "                 |===|              \n" RESET);
    //printf(GOLD "                 |" YELLOW " # " GOLD "|              \n\n" RESET);
    //
    printf(CYAN "     🎉 " BOLD "CONGRATULATIONS!" RESET CYAN " Your get_next_line is perfect!\n" RESET);
    printf(GREEN "     ✓ All edge cases handled\n" RESET);
    printf(GREEN "     ✓ Memory management is flawless\n" RESET);
    printf(GREEN "     ✓ Ready for submission!\n\n" RESET);
}

void display_failure_message(void) {
    printf("\n");
    printf(RED "     ╔═════════════════════════════════════════════════════════════╗\n" RESET);
    printf(RED "     ║               " BLINK "❌ SOME TESTS FAILED! ❌" RESET RED "                   ║\n" RESET);
    printf(RED "     ╚═════════════════════════════════════════════════════════════╝\n\n" RESET);
    
    printf(RED "             ▄▄▄▄▄▄▄▄▄▄▄\n" RESET);
    printf(RED "           ▄█" RESET WHITE "▀" RED "███████" RESET WHITE "▀" RED "█▄\n" RESET);
    printf(RED "          ██" RESET RED "▄" WHITE "▀▀▀▀▀▀▀▀▀" RED "▄" WHITE "██\n" RESET);
    printf(RED "          ▀████" RESET WHITE "▀▀▀▀▀" RED "████▀\n" RESET);
    printf(RED "            ▀████████████▀\n" RESET);
    printf(RED "        ▄▄▄▄▄▄▀" RESET WHITE "▀" RED "██████" RESET WHITE "▀" RED "▀▄▄▄▄▄▄\n" RESET);
    printf(RED "      ▄█" RESET WHITE "▀" RED "██" RESET WHITE "▀" RED "█" RESET WHITE "▀▀▀▀▀▀▀▀▀▀" RED "█" RESET WHITE "▀" RED "██" RESET WHITE "▀" RED "█▄\n" RESET);
    printf(RED "     ██" RESET WHITE "▀" RED "██" RESET WHITE "▀" RED "█" RESET WHITE "             " RED "█" RESET WHITE "▀" RED "██" RESET WHITE "▀" RED "██\n" RESET);
    printf(RED "     ██" RESET WHITE "●" RED "██" RESET WHITE "●" RED "█" RESET WHITE "     ☹︎       " RED "█" RESET WHITE "●" RED "██" RESET WHITE "●" RED "██\n" RESET);
    printf(RED "     ██" RESET WHITE "▄" RED "██" RESET WHITE "▄" RED "█" RESET WHITE "             " RED "█" RESET WHITE "▄" RED "██" RESET WHITE "▄" RED "██\n" RESET);
    printf(RED "      ▀█" RESET WHITE "▄" RED "██" RESET WHITE "▄" RED "█" RESET WHITE "▄▄▄▄▄▄▄▄▄▄▄" RED "█" RESET WHITE "▄" RED "██" RESET WHITE "▄" RED "█▀\n" RESET);
    printf(RED "        ▀▀▀▀▀" RESET WHITE "▄" RED "██████" RESET WHITE "▄" RED "▀▀▀▀▀\n" RESET);
    printf(RED "            ▀████████████▀\n" RESET);
    printf(RED "          ▄████" RESET WHITE "▄▄▄▄▄" RED "████▄\n" RESET);
    printf(RED "          ██" RESET RED "▀" WHITE "▄▄▄▄▄▄▄▄▄" RED "▀" WHITE "██\n" RESET);
    printf(RED "           ▀█" RESET WHITE "▄" RED "███████" RESET WHITE "▄" RED "█▀\n" RESET);
    printf(RED "             ▀▀▀▀▀▀▀▀▀▀▀\n\n" RESET);
    
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
    printf(CYBER2 "     ┃  " BOLD "GET_NEXT_LINE" RESET CYBER2 " - ULTIMATE TEST SUITE                  ┃\n" RESET);
    printf(CYBER3 "     ┃  " RESET YELLOW "Version 2.0" RESET CYBER3 "                                          ┃\n" RESET);
    printf(CYBER4 "     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n" RESET);
    
    printf(MAGENTA "     ╭───────────────────────────────────────────────────────────────────╮\n" RESET);
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
    
    printf(MAGENTA "     ╰─────────────────────────────────────────────────────────────╯\n\n" RESET);
    
    printf(CYBER2 "     📋 Testing your get_next_line implementation...\n" RESET);
    printf(CYBER3 "     🛠️  Checking various edge cases and file formats...\n" RESET);
    printf(CYBER4 "     ⚡ Running high-performance validations...\n\n" RESET);
    
    fflush(stdout);
    usleep(800000);
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
