/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:50 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:51 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/gnl_wrapper.h"
#include "../header/logging.h"
#include "../../get_next_line.h"
#include <stdio.h>
#include <string.h>

char *gnl_wrapper(int fd)
{
    LOG_DEBUG("gnl_wrapper called with fd %d", fd);
    
    if (fd < 0) {
        LOG_WARNING("Invalid fd %d, returning NULL", fd);
        return NULL;
    }
    
    char *line = get_next_line(fd);
    
    if (line == NULL) {
        LOG_DEBUG("get_next_line returned NULL");
    } else if (strlen(line) > 50) {
        char truncated[54];
        strncpy(truncated, line, 50);
        truncated[50] = '\0';
        strcat(truncated, "...");
        LOG_DEBUG("get_next_line returned line (truncated): %s", truncated);
    } else {
        LOG_DEBUG("get_next_line returned: %s", line);
    }
    
    return line;
}
