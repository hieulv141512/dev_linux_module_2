#include "../inc/cpu_monitor.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// Calculate AVG usage for one core
double calculate_usage(CoreTimes prev, CoreTimes curr) {
    long long prev_total = prev.user + prev.nice + prev.system + prev.idle + prev.iowait + prev.irq + prev.softirq + prev.steal;
    long long curr_total = curr.user + curr.nice + curr.system + curr.idle + curr.iowait + curr.irq + curr.softirq + curr.steal;
    
    long long total_diff = curr_total - prev_total;
    long long idle_diff = curr.idle - prev.idle;
    
    if (total_diff == 0) return 0.0;
    
    return 100.0 * (1.0 - (double)idle_diff / total_diff);
}


CPUStats get_cpu_stats() {
    CPUStats stats = {0};
    
    // get info from file /proc/stat
    FILE *stat_file = fopen("/proc/stat", "r");
    if (!stat_file) {
        fprintf(stderr, "Error when opening file /proc/stat");
        return stats;
    }
    
    // Đếm số core
    int num_cores = 0;
    char line[256];
    while (fgets(line, sizeof(line), stat_file) != NULL) {
        if (strncmp(line, "cpu", 3) == 0 && line[3] >= '0' && line[3] <= '9') {
            num_cores++;
        }
    }
    fseek(stat_file, 0, SEEK_SET); // Đặt lại con trỏ file về đầu
    
    stats.num_cores = num_cores;
    stats.core_usages = (CoreTimes *)malloc(num_cores * sizeof(CoreTimes));
    
    CoreTimes *prev_times = (CoreTimes *)malloc(num_cores * sizeof(CoreTimes));
    CoreTimes *curr_times = (CoreTimes *)malloc(num_cores * sizeof(CoreTimes));
    
    // Đọc lần đầu
    fgets(line, sizeof(line), stat_file); // Bỏ qua dòng tổng
    for (int i = 0; i < num_cores; i++) {
        fscanf(stat_file, "cpu%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
               &i, &prev_times[i].user, &prev_times[i].nice, &prev_times[i].system, 
               &prev_times[i].idle, &prev_times[i].iowait, &prev_times[i].irq, 
               &prev_times[i].softirq, &prev_times[i].steal, &prev_times[i].guest, 
               &prev_times[i].guest_nice);
    }
    
    // Đợi 1 giây để lấy mẫu
    sleep(1);
    fseek(stat_file, 0, SEEK_SET); // Đặt lại con trỏ file về đầu
    
    // Đọc lần hai
    double total_prev_idle = 0, total_prev_non_idle = 0;
    double total_curr_idle = 0, total_curr_non_idle = 0;
    
    fgets(line, sizeof(line), stat_file); // Bỏ qua dòng tổng
    sscanf(line, "cpu %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
           &prev_times[0].user, &prev_times[0].nice, &prev_times[0].system, &prev_times[0].idle, 
           &prev_times[0].iowait, &prev_times[0].irq, &prev_times[0].softirq, 
           &prev_times[0].steal, &prev_times[0].guest, &prev_times[0].guest_nice);
    
    for (int i = 0; i < num_cores; i++) {
        fscanf(stat_file, "cpu%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
               &i, &curr_times[i].user, &curr_times[i].nice, &curr_times[i].system, 
               &curr_times[i].idle, &curr_times[i].iowait, &curr_times[i].irq, 
               &curr_times[i].softirq, &curr_times[i].steal, &curr_times[i].guest, 
               &curr_times[i].guest_nice);
        stats.core_usages[i].user = calculate_usage(prev_times[i], curr_times[i]);
    }
    
    // Tính phần trăm trung bình
    double total_prev_total = prev_times[0].user + prev_times[0].nice + prev_times[0].system + prev_times[0].idle + prev_times[0].iowait + prev_times[0].irq + prev_times[0].softirq + prev_times[0].steal;
    double total_curr_total = curr_times[0].user + curr_times[0].nice + curr_times[0].system + curr_times[0].idle + curr_times[0].iowait + curr_times[0].irq + curr_times[0].softirq + curr_times[0].steal;
    
    double total_diff = total_curr_total - total_prev_total;
    double idle_diff = curr_times[0].idle - prev_times[0].idle;
    
    if (total_diff > 0) {
        stats.average_usage = 100.0 * (1.0 - idle_diff / total_diff);
    }
    
    // Lấy tần số
    FILE *freq_file = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
    if (freq_file) {
        fscanf(freq_file, "%lf", &stats.frequency);
        stats.frequency /= 1000.0; // Chuyển từ kHz sang MHz
        fclose(freq_file);
    }
    
    // Lấy nhiệt độ (ví dụ trên một số hệ thống)
    FILE *temp_file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temp_file) {
        fscanf(temp_file, "%lf", &stats.temperature);
        stats.temperature /= 1000.0; // Chuyển từ millidegree C sang độ C
        fclose(temp_file);
    }
    
    fclose(stat_file);
    free(prev_times);
    free(curr_times);
    
    return stats;
}

// Hàm giải phóng bộ nhớ
void free_cpu_stats(CPUStats *stats) {
    if (stats && stats->core_usages) {
        free(stats->core_usages);
        stats->core_usages = NULL;
    }
}