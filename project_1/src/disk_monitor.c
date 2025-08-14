#include "../inc/disk_monitor.h"
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <stdlib.h>


DiskStats* get_disk_stats() {
    DiskStats *stats = (DiskStats*)malloc(sizeof(DiskStats));
    if (stats == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for DiskStats instance.\n");
        return NULL;
    }

    char line[512];
    char device[256], mounted_point[256], capacity_str[16];
    uint64_t total, used, free;
    int scanned_items;

    memset(stats, 0, sizeof(DiskStats));
    stats->partition_count = 0;

    FILE *fp = popen("df -kP", "r");
    if (!fp) {
        fprintf(stderr, "Error when running command: df -kP");
        return NULL;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        if (stats->partition_count >= MAX_PARTITIONS) {
            break;
        }

        scanned_items = sscanf(line, "%s %lu %lu %lu %s %s",
                               device, &total, &used, &free, capacity_str, mounted_point);
        
        if (scanned_items == 6) {
            PartitionsStats *partition = &stats->partitions[stats->partition_count];
            
            strncpy(partition->name, device, PARTITION_NAME_LEN - 1);
            strncpy(partition->mounted_point, mounted_point, MOUNTED_POINT_LEN - 1);
            strncpy(partition->capacity, capacity_str, CAPACITY_LEN - 1);
            
            // Convert KB to MB
            partition->total_space = total / 1024;
            partition->used_space = used / 1024;
            partition->free_space = free / 1024;
            
            stats->partition_count++;
            stats->partitions[stats->partition_count] = partition;
        }
    }
    pclose(fp);

    return stats;
}

void free_disk_stats(DiskStats *stats) {
    if (stats) {
        free(stats);
    }
}