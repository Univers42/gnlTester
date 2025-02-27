/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:38:53 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:38:56 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_WRAPPER_H
#define GNL_WRAPPER_H

/**
 * ════════════════════════════════════════════════════════════════════════════════
 * ║                         GET_NEXT_LINE WRAPPER                                ║
 * ════════════════════════════════════════════════════════════════════════════════
 */

/**
 * @brief Wrapper function for get_next_line with additional validation
 * 
 * @param fd File descriptor to read from
 * @return char* String read from the file, or NULL if an error occurred
 * 
 * @note Provides additional error checking around get_next_line
 * @note Performs validation on the returned string
 * @note Handles timeout detection and memory tracking
 * 
 * @warning Return value must be freed by the caller
 * @warning Return value may be NULL if get_next_line fails or returns NULL
 */
char *gnl_wrapper(int fd);

#endif // GNL_WRAPPER_H
