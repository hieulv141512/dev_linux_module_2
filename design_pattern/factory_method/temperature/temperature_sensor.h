#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../sensor_factory/sensor.h"

// Function prototypes for the temperature sensor
Sensor* createTemperatureSensor(const char* id);

float temperatureSensorReadData(Sensor* sensor);

#endif //TEMPERATURE_SENSOR_H