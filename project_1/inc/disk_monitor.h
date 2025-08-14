#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "data_structures.h"

DiskStats* get_disk_stats();
void free_disk_stats(DiskStats *stats);

#endif // DISK_MONITOR_H