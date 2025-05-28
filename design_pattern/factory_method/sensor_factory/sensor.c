#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

// Function implementations
void sensorInitializeCommon(Sensor* sensor, SensorType type, const char* id, ReadDataFunc readData){
    if (sensor == NULL) {
        return;
    }
    snprintf(sensor->id, MAX_SIZE_ID, "%s", id);
    sensor->type = type;
    sensor->currentValue = readData(sensor);
}

void printSensorInfo(const Sensor* sensor){
    if (sensor == NULL) {
        return;
    }
    printf("\n------ Sensor Information ------\n");
    printf(" Sensor ID: %s", sensor->id);
    printf(" Sensor Type: ");
    switch (sensor->type)
    {
        case SENSOR_TYPE_TEMPERATURE:
            printf("Temperature. \n");
            break;
        case SENSOR_TYPE_HUMIDITY:
            printf("Humidity. \n");
            break;
        case SENSOR_TYPE_PRESSURE:
            printf("Pressure. \n");
            break;
        case SENSOR_TYPE_LIGHT:
            printf("Light. \n");
            break;
        default:
            printf("Unknown.\n");
            break;
    }
    printf(" Sensor Value: %.2f", sensor->currentValue);
}

void destroySensor(Sensor* sensor){
    if (sensor != NULL) {
        free(sensor);
    }
}