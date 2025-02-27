#ifndef DEFINES_H
# define DEFINES_H
# define RED         "\033[1;31m"
# define GREEN       "\033[1;32m"
# define YELLOW      "\033[1;33m"
# define BLUE        "\033[1;34m"
# define MAGENTA     "\033[1;35m"
# define CYAN        "\033[1;36m"
# define WHITE       "\033[1;37m"
# define RESET       "\033[0m"
# define BOLD        "\033[1m"
# define UNDERLINE   "\033[4m"
# define BLINK       "\033[5m"
# define BG_BLACK    "\033[40m"
# define BG_RED      "\033[41m"
# define BG_GREEN    "\033[42m"
# define BG_YELLOW   "\033[43m"
# define BG_BLUE     "\033[44m"
# define BG_MAGENTA  "\033[45m"
# define BG_CYAN     "\033[46m"
# define BG_WHITE    "\033[47m"
# define CYBER1      "\033[38;5;45m"   // Electric Blue
# define CYBER2      "\033[38;5;201m"  // Neon Pink
# define CYBER3      "\033[38;5;47m"   // Toxic Green
# define CYBER4      "\033[38;5;220m"  // Holographic Yellow
# define CLEAR_SCREEN "\033[H\033[J"
# define MOVE_UP     "\033[1A"
# define CLEAR_LINE  "\033[K"
# define NEWLINE    "\n"

// Memory validation defines - make default behavior safer
# define MEMORY_PADDING_SIZE 8  // Memory padding size for validation
# define MEMORY_VALIDATE_HEAP 0 // Disable unsafe memory validation by default
# define TRACK_BUFFER_OVERFLOWS 0 // Disable unsafe buffer tracking by default

#endif