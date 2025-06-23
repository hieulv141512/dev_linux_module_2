#include "inc/sensor_factory/sensor_factory.h"
#include "inc/sensor_factory/sensor.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a temperature sensor
    Sensor* temperatureSensor = createSensor(SENSOR_TYPE_TEMPERATURE, "1");
    if (temperatureSensor != NULL) {
        printSensorInfo(temperatureSensor);
        destroySensor(temperatureSensor);
    }

    // Create a humidity sensor
    Sensor* humiditySensor = createSensor(SENSOR_TYPE_HUMIDITY, "2");
    if (humiditySensor != NULL) {
        printSensorInfo(humiditySensor);
        destroySensor(humiditySensor);
    }

    // Create a pressure sensor
    Sensor* pressureSensor = createSensor(SENSOR_TYPE_PRESSURE, "3");
    if (pressureSensor != NULL) {
        printSensorInfo(pressureSensor);
        destroySensor(pressureSensor);
    }

    // Create a light sensor
    Sensor* lightSensor = createSensor(SENSOR_TYPE_LIGHT, "4");
    if (lightSensor != NULL) {
        printSensorInfo(lightSensor);
        destroySensor(lightSensor);
    }

    return 0;
}