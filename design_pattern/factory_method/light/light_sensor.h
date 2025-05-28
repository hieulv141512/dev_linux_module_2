#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "../sensor_factory/sensor.h"

// Function prototypes for the Light sensor
Sensor* createLightSensor(const char* id);

float lightSensorReadData(Sensor* sensor);

#endif //LIGHT_SENSOR_H