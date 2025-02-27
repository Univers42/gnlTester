#include "../header/gnl_wrapper.h"
#include "../header/logging.h"
#include "../../get_next_line.h"
#include <stdio.h>
#include <string.h>  // Added for strlen, strncpy, strcat

char *gnl_wrapper(int fd)
{
    LOG_DEBUG("gnl_wrapper called with fd %d", fd);
    
    if (fd < 0) {
        LOG_WARNING("Invalid fd %d, returning NULL", fd);
        return NULL;
    }
    
    char *line = get_next_line(fd);
    
    // Handle NULL return or large lines without filling the terminal
    if (line == NULL) {
        LOG_DEBUG("get_next_line returned NULL");
    } else if (strlen(line) > 50) {
        // Truncate very long lines in the log
        char truncated[54]; // 50 chars + "..." + null terminator
        strncpy(truncated, line, 50);
        truncated[50] = '\0';
        strcat(truncated, "...");
        LOG_DEBUG("get_next_line returned line (truncated): %s", truncated);
    } else {
        LOG_DEBUG("get_next_line returned: %s", line);
    }
    
    return line;
}
