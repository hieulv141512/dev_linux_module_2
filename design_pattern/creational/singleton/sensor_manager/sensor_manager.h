#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_SENSOR_NODES    10
#define MAX_DATA_VALUE      100
#define MAX_SENSOR_TYPE     50

typedef struct {
    int id;
    char sensorType[MAX_SENSOR_TYPE];
    float value;
} SensorNode;

typedef struct {
    SensorNode sensorNodes[MAX_SENSOR_NODES];
    size_t dataCount;
    bool isDbConnected;
} SensorManager;

// Function declarations
SensorManager* getSensorManagerInstance();

void collectSensorData(SensorManager* manager, int sensorId, float value, const char* sensorType);

bool pushDataToDatabase(SensorManager* manager);

void setupDatabaseConnection(SensorManager* manager);

void destroySensorManagerInstance();

#endif // SENSOR_MANAGER_H