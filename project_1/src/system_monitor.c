#include "../inc/system_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>


SystemStats* get_system_stats() {
    SystemStats *stats = (SystemStats *)malloc(sizeof(SystemStats));
    if (!stats) {
        fprintf(stderr, "Error: Failed to allocate memory for SystemStats instance.\n");
        return NULL;
    }
    
    FILE *fp;
    fp = fopen("/proc/loadavg", "r");
    if (fp) {
        float load_1, load_5, load_15;
        
        if (fscanf(fp, "%f %f %f", &load_1, &load_5, &load_15) == 3) {
            stats->load_avg_1 = load_1;
            stats->load_avg_5 = load_5;
            stats->load_avg_15 = load_15;
        } else {
            stats->load_avg_1 = 0.0;
            stats->load_avg_5 = 0.0;
            stats->load_avg_15 = 0.0;
        }
        fclose(fp);
    } else {
        fprintf(stderr, "Error when opening file /proc/loadavg\n");
        free(stats);
        return NULL;
    }

    fp = fopen("/proc/uptime", "r");
    if (fp) {
        double uptime_double;

        if (fscanf(fp, "%lf", &uptime_double) == 1) {
            stats->uptime_seconds = (long)uptime_double;
        } else {
            stats->uptime_seconds = 0;
        }
        fclose(fp);
    } else {
        fprintf(stderr, "Error when opening file /proc/uptime\n");
        free(stats);
        return NULL;
    }

    struct utsname uname_data;
    if (uname(&uname_data) == 0) {
        snprintf(stats->kernel_version, KERNEL_VERSION_LEN, "%s %s %s",
                 uname_data.sysname, uname_data.release, uname_data.version);
    } else {
        strcpy(stats->kernel_version, "Can't get kernel version\n");
    }

    return stats;
}

void free_system_stats(SystemStats *stats) {
    if (stats) {
        free(stats);
    }
}