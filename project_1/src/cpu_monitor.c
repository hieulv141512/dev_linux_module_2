#include "../inc/cpu_monitor.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// Calculate AVG usage
double calculate_usage(CoreTimes prev, CoreTimes curr) {
    long prev_total = prev.user + prev.nice + prev.system + prev.idle + prev.iowait + prev.irq + prev.softirq + prev.steal;
    long curr_total = curr.user + curr.nice + curr.system + curr.idle + curr.iowait + curr.irq + curr.softirq + curr.steal;
    
    long total_diff = curr_total - prev_total;
    long idle_diff = curr.idle - prev.idle;
    
    if (total_diff == 0) return 0.0;
    
    return 100.0 * (1.0 - (double)idle_diff / total_diff);
}


CPUStats* get_cpu_stats() {
    CPUStats *stats = (CPUStats*)malloc(sizeof(CPUStats));
    if (stats == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for CPUStats instance.\n");
        return NULL;
    }

    // Counting number of core processors
    int num_cores = 0;
    char line[256];

    FILE *stat_file = fopen("/proc/stat", "r");
    if (!stat_file) {
        fprintf(stderr, "Error when opening file /proc/stat");
        free(stats);
        return NULL;
    }
    
    while (fgets(line, sizeof(line), stat_file) != NULL) {
        if (strncmp(line, "cpu", 3) == 0) {
            num_cores++;
        }
    }
    stats->num_cores = num_cores;

    fseek(stat_file, 0, SEEK_SET);
    
    CoreTimes *core_usages = (CoreTimes*)malloc(num_cores * sizeof(CoreTimes));
    CoreTimes *prev_times = (CoreTimes *)malloc(num_cores * sizeof(CoreTimes));
    CoreTimes *curr_times = (CoreTimes *)malloc(num_cores * sizeof(CoreTimes));

    if (core_usages == NULL || prev_times == NULL || curr_times == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for instances.\n");
        free(stats);
        return NULL;
    }
    stats->core_usages = core_usages;

    // Read first time
    fgets(line, sizeof(line), stat_file);
    for (int i = 0; i < num_cores; i++) {
        fscanf(stat_file, "%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
            &prev_times[i].cpu_name, &prev_times[i].user, &prev_times[i].nice, 
            &prev_times[i].system, &prev_times[i].idle, &prev_times[i].iowait, 
            &prev_times[i].irq, &prev_times[i].softirq, &prev_times[i].steal, 
            &prev_times[i].guest, &prev_times[i].guest_nice);
    }
    
    sleep(1);
    fseek(stat_file, 0, SEEK_SET);
    
    // Read second time after sleep 1s & calculate usage
    for (int i = 0; i < num_cores; i++) {
        fscanf(stat_file, "%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
            &curr_times[i].cpu_name, &curr_times[i].user, &curr_times[i].nice, 
            &curr_times[i].system, &curr_times[i].idle, &curr_times[i].iowait, 
            &curr_times[i].irq, &curr_times[i].softirq, &curr_times[i].steal, 
            &curr_times[i].guest, &curr_times[i].guest_nice);
        core_usages[i].user = calculate_usage(prev_times[i], curr_times[i]);
    }
    stats->overall_usage = core_usages[0].user;
    
    // Get CPU frequency
    char buffer[256];
    float cpu_mhz = 0.0;

    FILE *freq_file = fopen("/proc/cpuinfo", "r");
    if (freq_file == NULL) {
        fprintf(stderr, "Error when opening file /proc/cpuinfo");
        free(stats);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), freq_file) != NULL) {
        if (sscanf(buffer, "cpu MHz : %f", &cpu_mhz) == 1) {
            break;
        }
    }
    stats->frequency = cpu_mhz;
    fclose(freq_file);
    
    // Get CPU temperature
    float cpu_temperature = 0.0;
    FILE *temp_file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temp_file) {
        fscanf(temp_file, "%lf", &cpu_temperature);
        cpu_temperature /= 1000.0;
        fclose(temp_file);
    }
    stats->cpu_temperature = cpu_temperature;
    
    fclose(stat_file);
    free(prev_times);
    free(curr_times);
    
    return stats;
}

// Free memory
void free_cpu_stats(CPUStats *stats) {
    if (stats && stats->core_usages) {
        free(stats->core_usages);
        stats->core_usages = NULL;
        free(stats);
    }
}