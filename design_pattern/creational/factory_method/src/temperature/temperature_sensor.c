#include "../../inc/temperature/temperature_sensor.h"
#include <stdlib.h>
#include <stdio.h>

float temperatureSensorReadData(Sensor* sensor) {
    if (sensor == NULL) {
        fprintf(stderr, "Error: NULL sensor cannot read data.\n");
        return -1;
    }
    // Generate random value from 20.0 to 35.0
    float tmpValue = 20.0f + ((float)rand() / RAND_MAX) * 15.0f;
    return tmpValue;
}

Sensor* createTemperatureSensor(const char* id) {
    Sensor* newSensor = (Sensor*)malloc(sizeof(Sensor));
    if (newSensor == NULL) {
        fprintf(stderr, "Failed to allocate memory for Temperature Sensor.\n");
        return NULL;
    }

    // Initialize common sensor properties
    sensorInitializeCommon(newSensor, SENSOR_TYPE_TEMPERATURE, id, temperatureSensorReadData);
    printf("Temperature Sensor %s is created. \n", id);
    
    return newSensor;
}