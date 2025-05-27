#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../sensor_factory/sensor.h"

typedef struct {
    Sensor base;
    float currentValue;
} TemperatureSensor;

// Function prototypes for the temperature sensor
TemperatureSensor* createTemperatureSensor(const char* id);

float temperatureSensorReadData(TemperatureSensor* sensor);

#endif //TEMPERATURE_SENSOR_H