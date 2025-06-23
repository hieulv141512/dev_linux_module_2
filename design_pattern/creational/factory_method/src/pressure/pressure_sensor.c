#include "../../inc/pressure/pressure_sensor.h"
#include <stdlib.h>
#include <stdio.h>

float pressureSensorReadData(Sensor* sensor) {
    if (sensor == NULL) {
        fprintf(stderr, "Error: NULL sensor cannot read data.\n");
        return -1;
    }
    // Generate random value from 30.0 to 40.0
    float tmpValue = 30.0f + ((float)rand() / RAND_MAX) * 10.0f;
    return tmpValue;
}

Sensor* createPressureSensor(const char* id) {
    Sensor* newSensor = (Sensor*)malloc(sizeof(Sensor));
    if (newSensor == NULL) {
        fprintf(stderr, "Failed to allocate memory for Pressure Sensor.\n");
        return NULL;
    }

    // Initialize common sensor properties
    sensorInitializeCommon(newSensor, SENSOR_TYPE_PRESSURE, id, pressureSensorReadData);
    printf("Pressure Sensor %s is created. \n", id);
    
    return newSensor;
}