#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include "sensor.h"

Sensor* createSensor(SensorType type, const char* id);

#endif // SENSOR_FACTORY_H