#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "data_structures.h"

SystemStats create_system_monitor_instance();

void get_system_stats(SystemStats *stats);

#endif // SYSTEM_MONITOR_H