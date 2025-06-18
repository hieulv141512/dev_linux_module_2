#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

void handleWateringAutoMode(uint32_t currentTimeSec);
void handleWateringManual(uint32_t currentTimeSec);

#endif // WATERING_LOGIC_H