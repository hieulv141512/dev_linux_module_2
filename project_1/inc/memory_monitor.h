#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "data_structures.h"

MemoryStats* get_memory_stats();
void free_memory_stats(MemoryStats *stats);

#endif // MEMORY_MONITOR_H