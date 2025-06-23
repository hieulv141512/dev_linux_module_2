#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "../sensor_factory/sensor.h"

// Function prototypes for the Pressure sensor
Sensor* createPressureSensor(const char* id);

float pressureSensorReadData(Sensor* sensor);

#endif //PRESSURE_SENSOR_H