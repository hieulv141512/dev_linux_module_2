#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "data_structures.h"

CPUStats* get_cpu_stats();
void free_cpu_stats(CPUStats *stats);

#endif // CPU_MONITOR_H