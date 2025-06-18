#include "../inc/system_state.h"
#include <stdio.h>
#include <stdbool.h>

SensorData globalSensorData = {0, 0};
SystemSettings globalSystemSettings;
PumpState globalPumpState = PUMP_OFF;
LEDState globalLedState = LED_NORMAL;

uint32_t globalLastSensorCheckTime = 0;
uint32_t globalWateringStartTime = 0;
bool globalIsManualWateringActive = false;

void systemStateInit(void) {
    globalSystemSettings.minMoistureThreshold = DEFAULT_MIN_MOISTURE_THRESHOLD;
    globalSystemSettings.maxMoistureThreshold = DEFAULT_MAX_MOISTURE_THRESHOLD;
    globalSystemSettings.maxWateringDuration = DEFAULT_MAX_WATERING_DURATION_SEC;
    globalSystemSettings.sensorCheckInterval = DEFAULT_SENSOR_CHECK_INTERVAL_SEC;
    globalSystemSettings.currentMode = MODE_AUTO;
    globalSystemSettings.manualWateringDuration = DEFAULT_MANUAL_WATERING_DURATION_SEC;

    globalPumpState = PUMP_OFF;
    globalLedState = LED_NORMAL;

    printf("System State Initialized. Default Mode: AUTO\n");
}