#ifndef COSMETICS_H
# define COSMETICS_H
# include "test_utils.h"
# include <stdbool.h>

void display_success_message(void);
void display_start_message(void);
void display_failure_message(void);
void display_test_header(size_t buffer_size);
void display_test_result(const char *filename, bool success, bool detailed);

#endif