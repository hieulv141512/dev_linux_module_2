#ifndef SENSOR_H
#define SENSOR_H

#define MAX_SIZE_ID 10

typedef struct Sensor Sensor;

typedef enum {
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_LIGHT,
    SENSOR_TYPE_UNKNOWN // Sentinel for error checking
} SensorType;

typedef float (*ReadDataFunc)(Sensor* sensor);

typedef struct {
    SensorType type;
    char id[MAX_SIZE_ID];
    ReadDataFunc readData;
} Sensor;

// Function declarations
void sensorInitializeCommon(Sensor* sensor, SensorType type, const char* id, ReadDataFunc readData);

void printSensorInfo(const Sensor* sensor);

void destroySensor(Sensor* sensor);

#endif // SENSOR_H