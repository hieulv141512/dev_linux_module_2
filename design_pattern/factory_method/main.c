#include "sensor_factory/sensor_factory.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a temperature sensor
    Sensor* temperatureSensor = createSensor(SENSOR_TYPE_TEMPERATURE, "1");
    if (temperatureSensor != NULL) {
        printSensorInfo(temperatureSensor);
        destroySensor(temperatureSensor);
    }

    return 0;
}