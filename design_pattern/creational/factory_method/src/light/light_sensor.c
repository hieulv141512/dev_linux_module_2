#include "../../inc/light/light_sensor.h"
#include <stdlib.h>
#include <stdio.h>

float lightSensorReadData(Sensor* sensor){
    if (sensor == NULL) {
        fprintf(stderr, "Error: NULL sensor cannot read data.\n");
        return -1;
    }
    // Generate random value from 60.0 to 70.0
    float tmpValue = 60.0f + ((float)rand() / RAND_MAX) * 10.0f;
    return tmpValue;
}

Sensor* createLightSensor(const char* id){
    Sensor* newSensor = (Sensor*)malloc(sizeof(Sensor));
    if (newSensor == NULL) {
        fprintf(stderr, "Failed to allocate memory for Light Sensor.\n");
        return NULL;
    }

    // Initialize common sensor properties
    sensorInitializeCommon(newSensor, SENSOR_TYPE_LIGHT, id, lightSensorReadData);
    printf("Light Sensor %s is created. \n", id);
    
    return newSensor;
}