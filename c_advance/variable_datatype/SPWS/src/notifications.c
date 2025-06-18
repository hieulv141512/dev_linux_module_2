#include "../inc/notifications.h"
#include "../inc/config.h"
#include "../inc/system_state.h"
#include <stdio.h>

void sendStatus() {
    printf("--- SYSTEM STATUS ---\n");
    printf("Mode: %s\n", globalSystemSettings.currentMode == MODE_AUTO ? "AUTO" : "MANUAL");
    printf("Pump: %s\n", globalPumpState == PUMP_ON ? "ON" : "OFF");
    printf("Soil Moisture: %d%%\n", globalSensorData.soilMoisturePercent);
    printf("Temperature: %dC\n", globalSensorData.environmentTemperature);
    printf("LED: ");
    switch (globalLedState) {
        case LED_NORMAL: printf("NORMAL (Green)\n"); break;
        case LED_WATERING: printf("WATERING (Yellow)\n"); break;
        case LED_LOW_MOISTURE_ALERT: printf("LOW MOISTURE (Blue)\n"); break;
        case LED_ERROR: printf("ERROR (Red)\n"); break;
        default: printf("UNKNOWN\n"); break;
    }
    printf("---------------------\n");
}

void sendMessage(const char* message) {
    printf("[NOTIFICATION] %s\n", message);
}