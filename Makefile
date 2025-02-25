################################################################################
#                                     CONFIG                                   #
################################################################################
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic \
         -g -O2 -fno-omit-frame-pointer \
         -fsanitize=address,undefined,leak \
         -fsanitize-recover=address,undefined \
         -D_FORTIFY_SOURCE=2 -Wshadow -Wconversion -Wdouble-promotion
DFLAGS = -MMD -MF $(@:.o=.d)
AUTHOR = dlesieur
DATE = 25/02/2025
GNL_PATH = ./
NOVISU = 0

BUFFER_SIZES = 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
GNL_PATH = ../
GNL_SRCS = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
GNL_BONUS_SRCS = $(GNL_PATH)get_next_line_bonus.c $(GNL_PATH)get_next_line_utils_bonus.c

BUFFER_SIZES = 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
#GNL_SRCS = get_next_line.c get_next_line_utils.c
#gnl_bonus_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

################################################################################
#                                  OBJECT FILES                               #
################################################################################
##OBJS = main.o test_utils.o $(GNL_SRCS:.c=.o)
##OBJS_BONUS = main_bonus.o test_utils.o $(gnl_bonus_SRCS:.c=.o)

################################################################################
#                                 MAKEFILE RULES                              #
################################################################################

all: header tester tester_bonus

tester: main.o test_utils.o $(GNL_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester main.o test_utils.o $(GNL_SRCS:.c=.o)

tester_bonus: main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)
	$(CC) $(CFLAGS) -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o)

run_tests: tester tester_bonus
	@for size in $(BUFFER_SIZES); do \
		echo ""; \
		echo "Running tests with BUFFER_SIZE = $$size"; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester main.o test_utils.o $(GNL_SRCS:.c=.o); \
		./tester; \
		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester_bonus main_bonus.o test_utils.o $(GNL_BONUS_SRCS:.c=.o); \
		./tester_bonus; \
	done

header:
	@printf "\033[0;32mBuilding Project...\033[m\n"

##run_tests: tester tester_bonus
##	@for size in $(BUFFER_SIZES); do \
##		echo "\n\033[0;34m[Testing] \033[0;36mBUFFER_SIZE = $$size\033[m"; \
##		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester $(OBJS); \
##		if ./tester; then \
##			printf "\033[0;32m✅ Test Passed\033[m\n"; \
##		else \
##			printf "\033[0;31m❌ Test Failed\033[m\n"; \
##		fi; \
##		$(CC) $(CFLAGS) -DBUFFER_SIZE=$$size -o tester_bonus $(OBJS_BONUS); \
##		if ./tester_bonus; then \
##			printf "\033[0;32m✅ Bonus Test Passed\033[m\n"; \
##		else \
##			printf "\033[0;31m❌ Bonus Test Failed\033[m\n"; \
##		fi; \
##	done
m:
	./tester detailed

b:
	./tester_bonus

run_all:m b
%.o: %.c
	@printf "\033[0;34m[Compiling] \033[0;36m$<\033[m\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o *.d tester tester_bonus
	@printf "\033[0;31m[Clean] Removed object files and executables\033[m\n"

fclean: clean
	@rm -f tester tester_bonus
	@printf "\033[0;31m[Full Clean] Removed all compiled binaries\033[m\n"

re: fclean all

.PHONY: all run_tests clean fclean re
