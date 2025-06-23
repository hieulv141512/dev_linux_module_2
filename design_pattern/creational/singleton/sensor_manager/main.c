#include "sensor_manager.h"
#include <stdio.h>

int main() {
    // Create the first sensor manager instance
    SensorManager* manager1 = getSensorManagerInstance();
    if (manager1 == NULL) {
        fprintf(stderr, "Failed to create manager1.\n");
        return 1;
    }

    // Attemp to create a second sensor manager
    SensorManager* manager2 = getSensorManagerInstance();
    if (manager2 == NULL){
        printf("Failed to create manager2 because a instance already exists.\n");
    }

    // Connect to database
    setupDatabaseConnection(manager1);

    printf("\n ------ Collecting data ------\n");
    collectSensorData(manager1, 10, 30, "sensorLight");
    collectSensorData(manager1, 11, 20, "sensorTemperature");
    collectSensorData(manager1, 12, 50, "sensorHumidity");

    printf("\n ------ Pushing data ------\n");
    pushDataToDatabase(manager1);

    printf("\n ------ Collecting more data ------\n");
    collectSensorData(manager1, 13, 50, "sensorLight");
    collectSensorData(manager1, 14, 35, "sensorTemperature");

    printf("\n ------ Pushing more data ------\n");
    pushDataToDatabase(manager1);

    printf("\n ------ Testing buffer full ------\n");
    for (int i = 0; i < MAX_SENSOR_NODES + 2; i++) {
        collectSensorData(manager1, 20 + i, 10 * i, "sensorLight");
    }

    // Destroy SensorManager instance
    destroySensorManagerInstance();

    return 0;
}