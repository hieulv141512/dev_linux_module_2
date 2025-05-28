#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "../sensor_factory/sensor.h"

// Function prototypes for the Humidity sensor
Sensor* createHumiditySensor(const char* id);

float humiditySensorReadData(Sensor* sensor);

#endif // HUMIDITY_SENSOR_H