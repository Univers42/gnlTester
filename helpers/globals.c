/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:44 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 20:39:45 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/globals.h"

bool stop_animation = false;
size_t total_test_count = 0;
size_t completed_tests = 0;
pthread_mutex_t progress_mutex = PTHREAD_MUTEX_INITIALIZER;
char current_test_name[100] = "Initializing...";
bool force_complete = false;