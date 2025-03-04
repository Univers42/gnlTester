# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 20:41:02 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/04 21:26:24 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################
CC = gcc

# Default compilation mode (normal or strict)
# Change this to 'strict' or run with 'make MODE=strict'
MODE ?= normal

# Compilation flags for normal mode (similar to 42 Moulinette)
NORMAL_CFLAGS = -Wall -Wextra -Werror \
                -g -O2 \
                -fno-omit-frame-pointer \
                -fsanitize=address,undefined,leak \
                -Iheader

# Compilation flags for strict mode (enhanced error checking)
STRICT_CFLAGS = -Wall -Wextra -Werror -pedantic \
                -g3 -O2 -fno-omit-frame-pointer \
                -fsanitize=address,undefined,leak,bounds \
                -fsanitize-recover=address,undefined \
                -D_FORTIFY_SOURCE=2 \
                -fstack-protector-strong \
                -Wshadow -Wconversion -Wdouble-promotion \
                -Wformat=2 -Wformat-truncation=2 -Wundef \
                -Wcast-align -Wwrite-strings -Wcast-qual \
                -Wunreachable-code -Wpointer-arith \
                -Wmissing-include-dirs -Wswitch-default \
                -Iheader
# Define separate flags for external files
GNL_CFLAGS = $(NORMAL_CFLAGS)

# Select flags based on mode
ifeq ($(MODE),strict)
    CFLAGS = $(STRICT_CFLAGS)
    MODE_DISPLAY = $(ERROR_COLOR)STRICT MODE$(NO_COLOR) \(Enhanced error checking\)
else
    CFLAGS = $(NORMAL_CFLAGS)
    MODE_DISPLAY = $(OK_COLOR)NORMAL MODE$(NO_COLOR) \(42 School Compatible\)
endif

DFLAGS = -MMD -MF $(@:.o=.d)
AUTHOR = dlesieur
DATE = 25/02/2025
GNL_PATH = ../

BUFFER_SIZES = 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
BOLD        = \033[1m

# Update LDFLAGS to include math library
LDFLAGS = -pthread -lm

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
# Main program sources in programs/ directory
PROGRAMS_SRCS = programs/main.c programs/main_bonus.c

# GNL source files
GNL_SRCS = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
GNL_BONUS_SRCS = $(GNL_PATH)get_next_line_bonus.c $(GNL_PATH)get_next_line_utils_bonus.c

# Helper source files in helpers/ directory
HELPER_SRCS = helpers/test_files.c helpers/globals.c helpers/cosmetics_utils.c \
              helpers/test_utils.c helpers/gnl_wrapper.c helpers/logging.c \
              helpers/memory_validate.c helpers/benchmarking.c

################################################################################
#                                  OBJECT FILES                               #
################################################################################
# Convert source paths to object paths
MAIN_OBJ = programs/main.o
MAIN_BONUS_OBJ = programs/main_bonus.o
HELPER_OBJS = $(HELPER_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
GNL_BONUS_OBJS = $(GNL_BONUS_SRCS:.c=.o)

OBJS = $(MAIN_OBJ) $(HELPER_OBJS) $(GNL_OBJS)
OBJS_BONUS = $(MAIN_BONUS_OBJ) $(HELPER_OBJS) $(GNL_BONUS_OBJS)

# Generate dependency files
DEPS = $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d)

################################################################################
#                                 MAKEFILE RULES                              #
################################################################################

all: header simple_build

header:
	@printf "\n$(OK_COLOR)╔═══════════════════════════════════════════════╗$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║             Building GNL Tester               ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)╚═══════════════════════════════════════════════╝$(NO_COLOR)\n\n"
	@printf "Compilation Mode: %b\n" "$(MODE_DISPLAY)"
	@printf "Use '$(COM_COLOR)make MODE=normal$(NO_COLOR)' for 42 School compatible mode\n"
	@printf "Use '$(COM_COLOR)make MODE=strict$(NO_COLOR)' for enhanced error checking\n\n"

# Create directories if they don't exist
init:
	@mkdir -p header helpers outputs programs

# Simple, reliable build without animations
simple_build: init tester tester_bonus
	@printf "\n$(OK_COLOR)╔═════════════════════════════════════════════════╗$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ██████╗  ██████╗ ███╗   ██╗███████╗██╗         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ██╔══██╗██╔═══██╗████╗  ██║██╔════╝██║         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ██║  ██║██║   ██║██╔██╗ ██║█████╗  ██║         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ██║  ██║██║   ██║██║╚██╗██║██╔══╝  ╚═╝         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ██████╔╝╚██████╔╝██║ ╚████║███████╗██╗         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)║  ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝         ║$(NO_COLOR)\n"
	@printf "$(OK_COLOR)╚═════════════════════════════════════════════════╝$(NO_COLOR)\n"

# Prevent make from removing intermediate files
.SECONDARY: $(OBJS) $(OBJS_BONUS)

# Include dependency files
-include $(DEPS)

# Object file rules with dependency generation
%.o: %.c
	@printf "$(COM_COLOR)[Compiling]$(NO_COLOR) $<\n"
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

# Special rule for GNL files
$(GNL_PATH)%.o: $(GNL_PATH)%.c
	@printf "$(COM_COLOR)[Compiling GNL]$(NO_COLOR) $<\n"
	@$(CC) $(GNL_CFLAGS) $(DFLAGS) -c $< -o $@

# Build tester executable (removed duplicate rule)
tester: $(OBJS)
	@printf "$(OK_COLOR)[Building]$(NO_COLOR) Linking tester executable...\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "$(OK_COLOR)[Success]$(NO_COLOR) Built tester executable!\n"

# Build tester_bonus executable (removed duplicate rule)
tester_bonus: $(OBJS_BONUS)
	@printf "$(OK_COLOR)[Building]$(NO_COLOR) Linking tester_bonus executable...\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "$(OK_COLOR)[Success]$(NO_COLOR) Built tester_bonus executable!\n"

# Simple test target - this is a minimal test to verify that get_next_line works
simple_test: simple_test_check.c $(GNL_SRCS)
	@printf "$(OK_COLOR)[Building]$(NO_COLOR) Compiling simple test...\n"
	@$(CC) $(GNL_CFLAGS) -D BUFFER_SIZE=42 -o $@ $^
	@printf "$(OK_COLOR)[Running]$(NO_COLOR) Simple test with BUFFER_SIZE=42:\n\n"
	@./$@
	@printf "\n$(OK_COLOR)[Done]$(NO_COLOR) Simple test completed!\n"

# Help target
help:
	@printf "\n$(OK_COLOR)GNL Tester - Compilation Modes:$(NO_COLOR)\n\n"
	@printf "$(BOLD)Available modes:$(NO_COLOR)\n"
	@printf "  - $(OK_COLOR)normal$(NO_COLOR): Compatible with 42 School Moulinette\n"
	@printf "    Basic warnings and error checking\n\n"
	@printf "  - $(ERROR_COLOR)strict$(NO_COLOR): Enhanced error checking\n"
	@printf "    Catches more subtle bugs and enforces stricter coding standards\n\n"
	@printf "$(BOLD)Usage:$(NO_COLOR)\n"
	@printf "  make MODE=normal    # Default mode\n"
	@printf "  make MODE=strict    # Strict mode\n"
	@printf "  make help          # Show this help message\n\n"
	@printf "You can also set the mode permanently by editing the MODE variable in the Makefile.\n\n"

# Run tests with different buffer sizes
run_tests: tester tester_bonus
	@for size in $(BUFFER_SIZES); do \
		echo ""; \
		echo "Running tests with BUFFER_SIZE = $$size"; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester $(MAIN_OBJ) $(HELPER_OBJS) $(GNL_OBJS) $(LDFLAGS); \
		./tester short; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester_bonus $(MAIN_BONUS_OBJ) $(HELPER_OBJS) $(GNL_BONUS_OBJS) $(LDFLAGS); \
		./tester_bonus short; \
	done

# Convenience targets
m: tester
	@ASAN_OPTIONS=detect_leaks=0 strace -e read -o strace_log ./tester detailed >/dev/tty
	@grep -q 'read(.*, 0)' strace_log && { echo "Error: read with buffer size 0 detected!"; exit 1; } || true



b: tester_bonus
	@./tester_bonus detailed

run_all: m b

clean:
	@printf "$(ERROR_COLOR)[Clean] Removing object files and executables...$(NO_COLOR)\n"
	@rm -f programs/*.o helpers/*.o *.o *.d $(GNL_SRCS:.c=.o) $(GNL_BONUS_SRCS:.c=.o)
	@printf "$(ERROR_COLOR)[Clean] Removed object files and executables$(NO_COLOR)\n"

fclean: clean
	@printf "$(ERROR_COLOR)[Full Clean] Removing binaries...$(NO_COLOR)\n"
	@rm -f tester tester_bonus
	@printf "$(ERROR_COLOR)[Full Clean] Removed all compiled binaries$(NO_COLOR)\n"

re: fclean all

create_test_files:
	@./create_test_files.sh

.PHONY: all run_tests clean fclean re m b run_all header init help create_test_files
