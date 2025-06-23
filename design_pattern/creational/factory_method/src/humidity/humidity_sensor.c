#include "../../inc/humidity/humidity_sensor.h"
#include <stdlib.h>
#include <stdio.h>

float humiditySensorReadData(Sensor* sensor) {
    if (sensor == NULL) {
        fprintf(stderr, "Error: NULL sensor cannot read data.\n");
        return -1;
    }
    // Generate random value from 60.0 to 95.0
    float tmpValue = 60.0f + ((float)rand() / RAND_MAX) * 35.0f;
    return tmpValue;
}

Sensor* createHumiditySensor(const char* id) {
    Sensor* newSensor = (Sensor*)malloc(sizeof(Sensor));
    if (newSensor == NULL) {
        fprintf(stderr, "Failed to allocate memory for Humidity Sensor.\n");
        return NULL;
    }

    // Initialize common sensor properties
    sensorInitializeCommon(newSensor, SENSOR_TYPE_HUMIDITY, id, humiditySensorReadData);
    printf("Humidity Sensor %s is created. \n", id);
    
    return newSensor;
}