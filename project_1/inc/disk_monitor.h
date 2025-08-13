#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "data_structures.h"

DiskStats create_disk_monitor_instance();

void get_disk_stats(DiskStats *stats);

#endif // DISK_MONITOR_H