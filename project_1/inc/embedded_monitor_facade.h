#ifndef EMBEDDED_MONITOR_FACADE_H
#define EMBEDDED_MONITOR_FACADE_H

#include "data_structures.h"

EmbeddedMonitorFacade* get_embedded_monitor_facade();

void check_thresholds_and_alert(const EmbeddedMonitorFacade *facade, const MonitorThresholds *thresholds);
void log_events(const char *message);
void free_embedded_monitor_facade(EmbeddedMonitorFacade *facade);

#endif // EMBEDDED_MONITOR_FACADE_H