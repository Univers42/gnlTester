/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmarking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:39:36 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/02/27 21:06:51 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/benchmarking.h"
#include "../header/defines.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static BenchmarkResults benchmark_results = {
    .memory_peak = 0,
    .memory_leaks = 0,
    .time_elapsed = 0,
    .efficiency_score = 0,
    .buffer_efficiency = 0,
    .edge_case_score = 0
};

static size_t memory_allocated = 0;
static size_t memory_peak = 0;
static size_t memory_freed = 0;
static size_t allocation_count = 0;
static size_t free_count = 0;
static struct timeval start_time, end_time;

void start_benchmark(void) {
    memory_allocated = 0;
    memory_peak = 0;
    memory_freed = 0;
    allocation_count = 0;
    free_count = 0;
    
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    // Fix sign conversion with explicit cast
    benchmark_results.memory_peak = (size_t)r_usage.ru_maxrss;
    
    gettimeofday(&start_time, NULL);
}

void benchmark_track_alloc(size_t size) {
    memory_allocated += size;
    if (memory_allocated > memory_peak) {
        memory_peak = memory_allocated;
    }
    allocation_count++;
}

void benchmark_track_free(size_t size) {
    memory_freed += size;
    memory_allocated -= size;
    free_count++;
}

const char* get_star_rating(double score) {
    if (score >= 90) return GOLD "★★★★★" RESET;
    if (score >= 80) return GOLD "★★★★" SILVER "★" RESET;
    if (score >= 70) return GOLD "★★★" SILVER "★★" RESET;
    if (score >= 60) return GOLD "★★" SILVER "★★★" RESET;
    if (score >= 50) return GOLD "★" SILVER "★★★★" RESET;
    return SILVER "★★★★★" RESET;
}

const char* get_performance_text(double score) {
    if (score >= 90) return GREEN "Exceptional" RESET;
    if (score >= 80) return GREEN "Excellent" RESET;
    if (score >= 70) return YELLOW "Very Good" RESET;
    if (score >= 60) return YELLOW "Good" RESET;
    if (score >= 50) return YELLOW "Average" RESET;
    return RED "Needs Improvement" RESET;
}

double calculate_buffer_efficiency(size_t *buffer_times, size_t count) {
    if (count <= 1) return 0.0;
    
    double sum = 0.0;
    for (size_t i = 0; i < count; i++) {
        // Fix conversion with explicit cast
        sum += (double)buffer_times[i];
    }
    double avg = sum / (double)count;
    
    double variance_sum = 0.0;
    for (size_t i = 0; i < count; i++) {
        // Fix conversion with explicit cast
        double diff = (double)buffer_times[i] - avg;
        variance_sum += diff * diff;
    }
    double variance = variance_sum / (double)count;
    double std_dev = sqrt(variance);
    
    double consistency = 100.0 - (std_dev / avg * 100.0);
    if (consistency < 0) consistency = 0.0;
    if (consistency > 100.0) consistency = 100.0;
    
    return consistency;
}

void stop_benchmark(bool all_tests_passed, double buffer_efficiency) {
    gettimeofday(&end_time, NULL);
    // Fix conversion with explicit casts
    double sec_diff = (double)(end_time.tv_sec - start_time.tv_sec);
    double usec_diff = (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double time_elapsed = sec_diff + usec_diff;
    
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    // Fix sign conversion with explicit cast
    size_t current_memory = (size_t)r_usage.ru_maxrss;
    
    if (current_memory > memory_peak) {
        memory_peak = current_memory;
    }
    
    size_t potential_leaks = (memory_allocated > memory_freed) ? 
                             memory_allocated - memory_freed : 0;
    
    // Fix conversion with explicit casts
    double memory_efficiency = (memory_peak > 0) ? 
                               100.0 - ((double)potential_leaks * 100.0 / (double)memory_peak) : 100.0;
    if (memory_efficiency < 0) memory_efficiency = 0.0;
    
    double time_efficiency = 100.0 - (time_elapsed * 5.0);
    if (time_efficiency < 0) time_efficiency = 0.0;
    if (time_efficiency > 100.0) time_efficiency = 100.0;
    
    double edge_case_score = all_tests_passed ? 100.0 : 0.0;
    
    double efficiency_score = (memory_efficiency * 0.4) + 
                              (time_efficiency * 0.2) + 
                              (buffer_efficiency * 0.2) + 
                              (edge_case_score * 0.2);
    
    benchmark_results.memory_peak = memory_peak;
    benchmark_results.memory_leaks = potential_leaks;
    benchmark_results.time_elapsed = time_elapsed;
    benchmark_results.efficiency_score = efficiency_score;
    benchmark_results.buffer_efficiency = buffer_efficiency;
    benchmark_results.edge_case_score = edge_case_score;
}

BenchmarkResults get_benchmark_results(void) {
    return benchmark_results;
}

void display_benchmark_results(void) {
    double code_quality = benchmark_results.edge_case_score * 0.8 + 
                          benchmark_results.buffer_efficiency * 0.2;
    double memory_usage = 100.0 - (benchmark_results.memory_leaks > 0 ? 100 : 0);
    double implementation = benchmark_results.efficiency_score;
    
    printf(CYAN "     ✨ " BOLD "Achievement Unlocked:" RESET "\n");
    printf(CYAN "     ├── " RESET "Code Quality:   %-12s   %s\n", 
           get_performance_text(code_quality), get_star_rating(code_quality));
    printf(CYAN "     ├── " RESET "Memory Usage:   %-12s   %s\n", 
           get_performance_text(memory_usage), get_star_rating(memory_usage));
    printf(CYAN "     └── " RESET "Implementation: %-12s   %s\n\n", 
           get_performance_text(implementation), get_star_rating(implementation));
}
