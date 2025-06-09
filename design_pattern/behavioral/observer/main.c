#include "inc/sensors/door_sensor.h"
#include "inc/sensors/motion_sensor.h"
#include "inc/sensors/smoke_sensor.h"
#include "inc/sensors/temperature_sensor.h"
#include "inc/subscribers/alarm_system_controller.h"
#include "inc/subscribers/hvac_system_controller.h"
#include "inc/subscribers/lighting_system_controller.h"
#include "inc/subscribers/mobile_app_notifier.h"

#include <stdio.h>

int main() {
    // Initialize sensors (publishers)
    DoorSensor doorSensor;
    doorSensorInit(&doorSensor);

    MotionSensor motionSensor;
    motionSensorInit(&motionSensor);

    SmokeSensor smokeSensor;
    smokeSensorInit(&smokeSensor);

    TemperatureSensor temperatureSensor;
    temperatureSensorInit(&temperatureSensor);

    // Initialize subscribers
    AlarmSystemController alarmSystem;
    alarmSystemControllerInit(&alarmSystem);

    HvacSystemController hvacSystem;
    hvacSystemControllerInit(&hvacSystem);

    LightingSystemController lightSystem;
    lightingSystemControllerInit(&lightSystem);

    MobileAppNotifier mobileApp;
    mobileAppNotifierInit(&mobileApp);

    // Register subscribers to door sensor
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&alarmSystem);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&hvacSystem);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&lightSystem);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&mobileApp);

    // Register subscribers to motion sensor
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&alarmSystem);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&hvacSystem);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&lightSystem);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&mobileApp);

    // Register subscribers to smoke sensor
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&alarmSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&hvacSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&lightSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&mobileApp);

    // Register subscribers to temperature sensor
    temperatureSensor.base.subscribe(&temperatureSensor.base, (Subscriber*)&alarmSystem);
    temperatureSensor.base.subscribe(&temperatureSensor.base, (Subscriber*)&hvacSystem);
    temperatureSensor.base.subscribe(&temperatureSensor.base, (Subscriber*)&lightSystem);
    temperatureSensor.base.subscribe(&temperatureSensor.base, (Subscriber*)&mobileApp);

    // Simulate events
    printf("== Simulate Door Open Event ==\n");
    doorSensorTrigger(&doorSensor, 1);

    printf("\n== Simulate Motion Detected Event ==\n");
    motionSensorTrigger(&motionSensor, 1);

    printf("\n== Simulate Smoke Detected Event ==\n");
    smokeSensorTrigger(&smokeSensor, 1);

    printf("\n== Simulate Temperature Raise Event ==\n");
    temperatureSensorTrigger(&temperatureSensor, 1);

    return 0;
}