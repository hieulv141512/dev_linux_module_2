#include "../inc/sensors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readData() {
    uint8_t sampleMoisture = (rand() % (DEFAULT_MAX_MOISTURE_THRESHOLD - DEFAULT_MIN_MOISTURE_THRESHOLD + 10)) + DEFAULT_MIN_MOISTURE_THRESHOLD;
    uint8_t sampleTemperature = (rand() % (DEFAULT_MAX_RANGE_TEMPERATURE - DEFAULT_MIN_RANGE_TEMPERATURE + 1)) + DEFAULT_MIN_RANGE_TEMPERATURE;
    
    globalSensorData.soilMoisturePercent = sampleMoisture;
    globalSensorData.environmentTemperature = sampleTemperature;

    printf("[SENSORS] Soil Moisture: %d%%, Temperature: %dC\n", 
           globalSensorData.soilMoisturePercent, globalSensorData.environmentTemperature);
}