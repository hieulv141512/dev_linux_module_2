#include "temperature_sensor.h"
#include <stdlib.h>
#include <stdio.h>


float temperatureSensorReadData(TemperatureSensor* sensor){
    if (sensor == NULL) {
        fprintf(stderr, "Error: NULL sensor cannot read data.\n");
        return -1;
    }
    // Generate random value from 20.0 to 35.0
    sensor->currentValue = 20.0f + ((float)rand() / RAND_MAX) * 15.0f;
    return sensor->currentValue;
}

TemperatureSensor* createTemperatureSensor(const char* id){
    TemperatureSensor* newSensor = (TemperatureSensor*)malloc(sizeof(TemperatureSensor));
    if (newSensor == NULL) {
        fprintf(stderr, "Failed to allocate memory for Temperature Sensor.\n");
        return NULL;
    }

    // Initialize common sensor properties
    sensorInitializeCommon(newSensor, SENSOR_TYPE_TEMPERATURE, id, temperatureSensorReadData);
    printf("Temperature Sensor %s is created. \n", id);
    
    return newSensor;
}


