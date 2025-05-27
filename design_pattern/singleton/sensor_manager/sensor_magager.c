#include "sensor_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Singleton instance
static SensorManager* singletonSensorManager = NULL;

static void initializeSensorManager(SensorManager* manager){
    manager->dataCount = 0;
    manager->isDbConnected = false;
    memset(manager->sensorNodes, 0, sizeof(manager->sensorNodes));
}

SensorManager* getSensorManagerInstance(){
    if (singletonSensorManager == NULL) {
        singletonSensorManager = (SensorManager*)malloc(sizeof(SensorManager));
        if (singletonSensorManager == NULL) {
            fprintf(stderr, "SensorManager: Failed to allocate memory for instance. \n");
            exit(EXIT_FAILURE);
        }

        initializeSensorManager(singletonSensorManager);
        printf("SensorManager: Unique instance created. \n");
    }
    else{
        printf("SensorManager: Return existing instance. \n");
        return NULL;
    }
    return singletonSensorManager;
}

void collectSensorData(SensorManager* manager, int sensorId, float value, const char* sensorType){
    if (manager == NULL) {
        fprintf(stderr, "SensorManager: Cannot collect data from NULL manager.\n");
        return;
    }

    if (manager->dataCount >= MAX_SENSOR_NODES) {
        printf("SensorManager: Data buffer full. Cannot collect more sensor data. \n");
        return;
    }

    printf("SensorManager: Collecting data from Sensor %d: Sensor Type = '%s' - Value = %.2f\n", sensorId, sensorType, value);
    manager->sensorNodes[manager->dataCount].id = sensorId;
    manager->sensorNodes[manager->dataCount].value = value;
    snprintf(manager->sensorNodes[manager->dataCount].sensorType, MAX_SENSOR_TYPE, "%s", sensorType);
    manager->dataCount++;
}

void setupDatabaseConnection(SensorManager* manager){
    if (manager == NULL) {
        fprintf(stderr, "SensorManager: Cannot setup database for NULL manager.\n");
        return;
    }

    printf("SensorManager: Setting up database connection...\n");
    manager->isDbConnected = true;
    printf("SensorManager: Database connected. \n");
}


bool pushDataToDatabase(SensorManager* manager){
    if (manager == NULL) {
        fprintf(stderr, "SensorManager: Cannot push data to database for NULL manager.\n");
        return false;
    }
    if (!manager->isDbConnected) {
        fprintf(stderr, "SensorManager: Database is not connected. Cannot push data.\n");
        return false;
    }
    if (manager->dataCount == 0) {
        printf("SensorManager: No data to push to database.\n");
        return false;
    }

    printf("SensorManager: Pushing %zu data points to database...\n", manager->dataCount);
    // Simulate database interaction (e.g., iterating through collectedData and "saving" it)
    for (size_t i = 0; i < manager->dataCount; i++) {
        printf("[DB] Saving Sensor %d: Sensor type = '%s' Value = %.2f\n", manager->sensorNodes[i].id, manager->sensorNodes[i].sensorType, manager->sensorNodes[i].value);
    }
    manager->dataCount = 0; // Clear collected data after pushing
    printf("SensorManager: Data pushed successfully.\n");
    return true;
}

void destroySensorManagerInstance(){
    if (singletonSensorManager != NULL) {
        printf("SensorManager: Destroying instance and freeing memory. \n");

        if (singletonSensorManager->isDbConnected) {
            printf("SensorManager: Closing database connection.\n");
            singletonSensorManager->isDbConnected = false;
        }

        free(singletonSensorManager);
        singletonSensorManager = NULL;
    }
    else {
        printf("SensorManager: No instance to destroy.\n");
    }
}