#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "config.h"
#include <stdbool.h>

extern SensorData globalSensorData;
extern SystemSettings globalSystemSettings;
extern PumpState globalPumpState;
extern LEDState globalLedState;

extern uint32_t globalLastSensorCheckTime;
extern uint32_t globalWateringStartTime;
extern bool globalIsManualWateringActive;

void systemStateInit(void);

#endif // SYSTEM_STATE_H