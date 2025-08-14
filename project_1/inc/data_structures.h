#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>

#define MAX_PARTITIONS 10
#define PARTITION_NAME_LEN 256
#define IP_ADDRESS_LEN 32
#define KERNEL_VERSION_LEN 256
#define CPU_NAME_LEN 16
#define MOUNTED_POINT_LEN 256
#define CAPACITY_LEN 16

// CPU info
typedef struct {
    char cpu_name[CPU_NAME_LEN];
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
    long guest;
    long guest_nice;
} CoreTimes;

typedef struct {
    float overall_usage;
    int num_cores;
    CoreTimes *core_usages;
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
    char mounted_point[MOUNTED_POINT_LEN];
    char capacity[CAPACITY_LEN];
    uint64_t total_space;
    uint64_t used_space;
    uint64_t free_space;
} PartitionsStats;

typedef struct {
    PartitionsStats *partitions[MAX_PARTITIONS];
    int partition_count;
    // float read_speed_kbps;
    // float write_speed_kbps;
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
    char kernel_version[KERNEL_VERSION_LEN];
    float load_avg_1;
    float load_avg_5;
    float load_avg_15;
} SystemStats;

// Embedded monitor facade
typedef struct {
    CPUStats *cpu_stats;
    MemoryStats *memory_stats;
    DiskStats *disk_stats;
    NetworkStats *network_stats;
    SystemStats *system_stats;
} EmbeddedMonitorFacade;

// Threshold
typedef struct {
    float cpu_usage_threshold_percent;
    float memory_usage_threshold_percent;
    float disk_usage_threshold_percent;
} MonitorThresholds;

#endif // DATA_STRUCTURES_H