#include "../../inc/sensors/temperature_sensor.h"
#include <stdio.h>

// Initialize the TemperatureSensor struct
void temperatureSensorInit(TemperatureSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->temperatureRaise = 0;
}

// Simulate a temperature event and notify subscribers
void temperatureSensorTrigger(TemperatureSensor* sensor, int raise) {
    sensor->temperatureRaise = raise;
    if (raise) {
        sensor->base.notifySubscribers(&sensor->base, "Temperature Raised");
    }
    else {
        sensor->base.notifySubscribers(&sensor->base, "No Temperature Raised");
    }
}