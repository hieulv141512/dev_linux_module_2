#include "inc/embedded_monitor_facade.h"
#include <stdio.h>

int main() {

    // MonitorThresholds thresholds = {
    //     .cpu_usage_threshold_percent = 80.0f,
    //     .memory_usage_threshold_percent = 85.0f,
    //     .disk_usage_threshold_percent = 90.0f,
    // };
    int n = 0;
    
    EmbeddedMonitorFacade *facade = get_embedded_monitor_facade();
    if (!facade) {
        return 1;
    }

    while (n < 10) {

        printf("\n--- System Monitor Dashboard ---\n");
        printf("CPU Usage: %.2f%%\n", facade->cpu_stats->overall_usage);
        printf("CPU Temp: %.2lf C\n", facade->cpu_stats->cpu_temperature);
        printf("CPU Frequency: %.2f\n", facade->cpu_stats->frequency);

        printf("RAM Usage: %.2f GB / %.2f GB\n", 
               (float)facade->memory_stats->used_ram / (1024),
               (float)facade->memory_stats->total_ram / (1024));

        printf("Download Speed: %.2f KB/s\n", facade->network_stats->current_download_speed_kbps);
        printf("Upload Speed: %.2f KB/s\n", facade->network_stats->current_upload_speed_kbps);

        printf("System uptime: %ld\n", facade->system_stats->uptime_seconds);
        printf("System kernel version: %s\n", facade->system_stats->kernel_version);
        printf("--------------------------------\n");

        n++;
        sleep(5);
    }

    free_embedded_monitor_facade(facade);

    return 0;
}