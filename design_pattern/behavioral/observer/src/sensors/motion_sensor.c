#include "../../inc/sensors/motion_sensor.h"
#include <stdio.h>

// Initialize the MotionSensor struct
void MotionSensorInit(MotionSensor* sensor){
    publisherInit(&sensor->base);
    sensor->motionDetected = 0;
}

// Simulate a motion event and notify subscribers
void motionSensorTrigger(MotionSensor* sensor, int detected){
    sensor->motionDetected = detected;
    if (detected) {
        sensor->base.notifySubscribers(&sensor->base, "Motion Detected");
    }
    else {
        sensor->base.notifySubscribers(&sensor->base, "No Motion Detected");
    }
}