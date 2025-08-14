#include "../inc/memory_monitor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


MemoryStats* get_memory_stats() {
    MemoryStats *stats = (MemoryStats*)malloc(sizeof(MemoryStats));
    if (stats == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for MemoryStats instance.\n");
        return NULL;
    }

    char line[256];
    char key[64];
    uint64_t value_kb;
    memset(stats, 0, sizeof(MemoryStats));

    FILE *mem_file = fopen("/proc/meminfo", "r");
    if (!mem_file) {
        fprintf(stderr, "Error when opening file /proc/meminfo");
        free(stats);
        return NULL;
    }

    while (fgets(line, sizeof(line), mem_file)) {
        if (sscanf(line, "%s %lu kB", key, &value_kb) == 2) {
            key[strlen(key)-1] = '\0';

            uint64_t value_mb = value_kb / 1024;

            if (strcmp(key, "MemTotal") == 0) {
                stats->total_ram = value_mb;
            } else if (strcmp(key, "MemFree") == 0) {
                stats->free_ram = value_mb;
            } else if (strcmp(key, "SwapTotal") == 0) {
                stats->total_swap = value_mb;
            } else if (strcmp(key, "SwapFree") == 0) {
                stats->free_swap = value_mb;
            } else if (strcmp(key, "Cached") == 0) {
                stats->cached = value_mb;
            }
        }
    }
    fclose(mem_file);
    stats->used_ram = stats->total_ram - stats->free_ram;
    stats->used_swap = stats->total_swap - stats->free_swap;

    return stats;
}


void free_memory_stats(MemoryStats *stats) {
    if (stats) {
        free(stats);
    }
}