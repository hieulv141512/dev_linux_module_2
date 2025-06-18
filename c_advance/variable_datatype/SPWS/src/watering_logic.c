#include "../inc/watering_logic.h"
#include "../inc/config.h"
#include "../inc/system_state.h"
#include "../inc/actuators.h"
#include "../inc/notifications.h"
#include "../inc/sensors.h"
#include <stdio.h> 

void handleWateringAutoMode(uint32_t currentTimeSec) {
    if ((currentTimeSec - globalLastSensorCheckTime) >= globalSystemSettings.sensorCheckInterval) {
        readData();
        globalLastSensorCheckTime = currentTimeSec;
        sendStatus();
    }

    if (globalPumpState == PUMP_OFF) {
        if (globalSensorData.soilMoisturePercent < globalSystemSettings.minMoistureThreshold) {
            setLedState(LED_LOW_MOISTURE_ALERT);
            turnPumpOn();
            globalWateringStartTime = currentTimeSec;
            sendMessage("Starting automatic watering. Soil moisture too low.");
            setLedState(LED_WATERING);
        } else {
            setLedState(LED_NORMAL);
        }
    } else {
        bool isStopWatering = false;
        if (globalSensorData.soilMoisturePercent >= globalSystemSettings.maxMoistureThreshold) {
            isStopWatering = true;
            sendMessage("Stopping automatic watering. Soil moisture reached maximum threshold.");
        } else if ((currentTimeSec - globalWateringStartTime) >= globalSystemSettings.maxWateringDuration) {
            isStopWatering = true;
            sendMessage("Stopping automatic watering. Max watering duration reached.");
        }
        if (isStopWatering) {
            turnPumpOff();
            setLedState(LED_NORMAL);
        } else {
            setLedState(LED_WATERING);
        }
    }

    if (globalPumpState == PUMP_OFF && globalSensorData.soilMoisturePercent < globalSystemSettings.minMoistureThreshold) {
         setLedState(LED_LOW_MOISTURE_ALERT);
    }
}

void handleWateringManual(uint32_t currentTimeSec) {
    if (globalIsManualWateringActive) {
        if ((currentTimeSec - globalWateringStartTime) >= globalSystemSettings.manualWateringDuration) {
            turnPumpOff();
            globalIsManualWateringActive = false;
            setLedState(LED_NORMAL);
            sendMessage("Manual watering finished.");
        } else {
            setLedState(LED_WATERING);
        }
    }
}