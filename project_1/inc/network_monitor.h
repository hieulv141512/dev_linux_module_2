#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include "data_structures.h"

NetworkStats* get_network_stats();

void free_network_stats(NetworkStats *stats);

#endif // NETWORK_MONITOR_H