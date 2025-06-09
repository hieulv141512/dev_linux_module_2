#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../publisher.h"

// Temperature sensor struct
typedef struct {
    Publisher base;
    int temperatureRaise;
} TemperatureSensor;

void temperatureSensorInit(TemperatureSensor* sensor);
void temperatureSensorTrigger(TemperatureSensor* sensor, int raise);

#endif // TEMPERATURE_SENSOR_H