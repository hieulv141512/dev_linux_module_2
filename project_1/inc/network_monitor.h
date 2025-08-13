#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include "data_structures.h"

NetworkStats create_network_monitor_instance();

void get_network_stats(NetworkStats *stats);

#endif // NETWORK_MONITOR_H