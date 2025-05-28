#include "sensor_factory.h"
#include "../temperature/temperature_sensor.h"
#include "../humidity/humidity_sensor.h"
#include "../light/light_sensor.h"
#include "../pressure/pressure_sensor.h"
#include "../temperature/temperature_sensor.h"
#include <stdlib.h>
#include <stdio.h>

Sensor* createSensor(SensorType type, const char* id){
    switch (type)
    {
        case SENSOR_TYPE_TEMPERATURE:
            return createTemperatureSensor(id);
        case SENSOR_TYPE_HUMIDITY:
            return createHumiditySensor(id);
        case SENSOR_TYPE_LIGHT:
            return createLightSensor(id);
        case SENSOR_TYPE_PRESSURE:
            return createPressureSensor(id);
        default:
            fprintf(stderr, "Error: Unknown sensor type.\n");
            return NULL;
    }
}