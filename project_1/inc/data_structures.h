#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>

#define MAX_PARTITIONS 10
#define PARTITION_NAME_LEN 64
#define IP_ADDRESS_LEN 32

// CPU info
typedef struct {
    float overall_usage;
    float core_usages[2];
    float cpu_temperature;
    float frequency;
} CPUStats;

// Memory info
typedef struct {
    uint64_t total_ram;
    uint64_t used_ram;
    uint64_t free_ram;
    uint64_t total_swap;
    uint64_t used_swap;
    uint64_t free_swap;
    uint64_t cached;
} MemoryStats;

// Disk info
typedef struct {
    char name[PARTITION_NAME_LEN];
    char mounted_point[PARTITION_NAME_LEN];
    uint64_t total_space;
    uint64_t used_space;
    uint64_t free_space;
} PartitionsStats;

typedef struct {
    PartitionsStats partitions[MAX_PARTITIONS];
    int partition_count;
    float read_speed_kbps;
    float write_speed_kbps;
} DiskStats;

// Network info
typedef struct {
    char ip_address[IP_ADDRESS_LEN];
    uint64_t num_connection;
    float current_download_speed_kbps;
    float current_upload_speed_kbps;
} NetworkStats;

// System info
typedef struct {
    long uptime_seconds;
    char kernel_version[256];
    float load_avg_1;
    float load_avg_5;
    float load_avg_15;
} SystemStats;

#endif // DATA_STRUCTURES_H