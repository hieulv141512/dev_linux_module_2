#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "data_structures.h"

MemoryStats create_memory_monitor_instance();

void get_memory_stats(MemoryStats *stats);

#endif // MEMORY_MONITOR_H