#include "../inc/embedded_monitor_facade.h"
#include "../inc/cpu_monitor.h"
#include "../inc/disk_monitor.h"
#include "../inc/memory_monitor.h"
#include "../inc/network_monitor.h"
#include "../inc/system_monitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void log_events(const char *message) {
    FILE *log_file = fopen("monitor.log", "a");
    if (!log_file) {
        fprintf(stderr, "Error when opening log file.\n");
        return;
    }
    
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    
    fprintf(log_file, "[%s] %s\n", time_str, message);
    fclose(log_file);
}

void play_beep_sound() {
    printf("\a");
    fflush(stdout);
}

void check_thresholds_and_alert(const EmbeddedMonitorFacade *facade, const MonitorThresholds *thresholds) {
    char log_message[256];
    int alert_triggered = 0;

    if (facade->cpu_stats->overall_usage > thresholds->cpu_usage_threshold_percent) {
        snprintf(log_message, sizeof(log_message), "Warning! CPU over threshold: %.2f%% > %.2f%%",
                 facade->cpu_stats->overall_usage, thresholds->cpu_usage_threshold_percent);
        printf("⚠️  %s\n", log_message);
        log_events(log_message);
        alert_triggered = 1;
    }

    float memory_usage_percent = (facade->memory_stats->used_ram / facade->memory_stats->total_ram) * 100.0f;
    if (memory_usage_percent > thresholds->memory_usage_threshold_percent) {
        snprintf(log_message, sizeof(log_message), "Warning! Memory over threshold: %.2f%% > %.2f%%",
                 memory_usage_percent, thresholds->memory_usage_threshold_percent);
        printf("⚠️  %s\n", log_message);
        log_events(log_message);
        alert_triggered = 1;
    }
    
    // float disk_usage_percent = (facade->disk_stats->used_space / facade->disk_stats->total_space) * 100.0f;
    // if (disk_usage_percent > thresholds->disk_usage_threshold_percent) {
    //     snprintf(log_message, sizeof(log_message), "Warning! Disk over threshold: %.2f%% > %.2f%%",
    //              disk_usage_percent, thresholds->disk_usage_threshold_percent);
    //     printf("⚠️  %s\n", log_message);
    //     log_event(log_message);
    //     alert_triggered = 1;
    // }
    
    if (alert_triggered) {
        play_beep_sound();
    }
}

EmbeddedMonitorFacade* get_embedded_monitor_facade() {
    EmbeddedMonitorFacade *facade = (EmbeddedMonitorFacade *)malloc(sizeof(EmbeddedMonitorFacade));
    if (facade == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for EmbeddedMonitorFacade instance.\n");
        return NULL;
    }
    facade->cpu_stats = get_cpu_stats();
    facade->memory_stats = get_memory_stats();
    facade->disk_stats = get_disk_stats();
    facade->network_stats = get_network_stats();
    facade->system_stats = get_system_stats();
}

void free_embedded_monitor_facade(EmbeddedMonitorFacade *facade) {
    if (facade) {
        free(facade->cpu_stats);
        free(facade->disk_stats);
        free(facade->memory_stats);
        free(facade->network_stats);
        free(facade->system_stats);
        free(facade);
    }
}