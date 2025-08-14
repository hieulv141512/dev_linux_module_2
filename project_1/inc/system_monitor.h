#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "data_structures.h"

SystemStats* get_system_stats();

void free_system_stats(SystemStats *stats);

#endif // SYSTEM_MONITOR_H