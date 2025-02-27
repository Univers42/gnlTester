/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:38 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:38:40 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                         TERMINAL COLOR DEFINITIONS                           ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define RED         "\033[1;31m"  ///< Bold red text
# define GREEN       "\033[1;32m"  ///< Bold green text
# define YELLOW      "\033[1;33m"  ///< Bold yellow text
# define BLUE        "\033[1;34m"  ///< Bold blue text
# define MAGENTA     "\033[1;35m"  ///< Bold magenta text
# define CYAN        "\033[1;36m"  ///< Bold cyan text
# define WHITE       "\033[1;37m"  ///< Bold white text
# define RESET       "\033[0m"     ///< Reset all formatting
# define BOLD        "\033[1m"     ///< Bold text
# define UNDERLINE   "\033[4m"     ///< Underlined text
# define BLINK       "\033[5m"     ///< Blinking text

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                      TERMINAL BACKGROUND DEFINITIONS                         ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define BG_BLACK    "\033[40m"    ///< Black background
# define BG_RED      "\033[41m"    ///< Red background
# define BG_GREEN    "\033[42m"    ///< Green background
# define BG_YELLOW   "\033[43m"    ///< Yellow background
# define BG_BLUE     "\033[44m"    ///< Blue background
# define BG_MAGENTA  "\033[45m"    ///< Magenta background
# define BG_CYAN     "\033[46m"    ///< Cyan background
# define BG_WHITE    "\033[47m"    ///< White background

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                        CYBERPUNK THEME COLOR PALETTE                         ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define CYBER1      "\033[38;5;45m"   ///< Electric blue color for cyberpunk theme
# define CYBER2      "\033[38;5;201m"  ///< Neon pink color for cyberpunk theme
# define CYBER3      "\033[38;5;47m"   ///< Toxic green color for cyberpunk theme
# define CYBER4      "\033[38;5;220m"  ///< Holographic yellow for cyberpunk theme

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                        TERMINAL CONTROL SEQUENCES                            ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define CLEAR_SCREEN "\033[H\033[J" ///< Clear screen and move cursor to top-left
# define MOVE_UP     "\033[1A"       ///< Move cursor up 1 line
# define CLEAR_LINE  "\033[K"        ///< Clear from cursor to end of line
# define NEWLINE     "\n"            ///< Newline character

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                           TROPHY/MEDAL COLORS                                ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define GOLD        "\033[38;5;220m"  ///< Rich gold color for first place
# define BRONZE      "\033[38;5;130m"  ///< Bronze/copper tone for third place
# define SILVER      "\033[38;5;7m"    ///< Silver/gray tone for second place

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                          DARK COLOR VARIATIONS                               ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define DARK_RED     "\033[0;31m"    ///< Dark red (non-bold)
# define DARK_GREEN   "\033[0;32m"    ///< Dark green (non-bold)
# define DARK_YELLOW  "\033[0;33m"    ///< Dark yellow/brown (non-bold)
# define DARK_BLUE    "\033[0;34m"    ///< Dark blue (non-bold)
# define DARK_MAGENTA "\033[0;35m"    ///< Dark magenta (non-bold)
# define DARK_CYAN    "\033[0;36m"    ///< Dark cyan (non-bold)
# define DARK_GRAY    "\033[0;90m"    ///< Dark gray (non-bold)
# define DARK         "\033[0;30m"    ///< Black/Dark black (non-bold)

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                         MEMORY VALIDATION SETTINGS                           ║
 * ════════════════════════════════════════════════════════════════════════════════
 */
# define MEMORY_PADDING_SIZE 8    ///< Memory padding size for validation in bytes
# define MEMORY_VALIDATE_HEAP 0   ///< Heap validation: 0=disabled, 1=enabled
# define TRACK_BUFFER_OVERFLOWS 0 ///< Buffer overflow detection: 0=disabled, 1=enabled

#endif // DEFINES_H