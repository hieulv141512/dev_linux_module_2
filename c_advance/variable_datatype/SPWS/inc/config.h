#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#define DEFAULT_MIN_MOISTURE_THRESHOLD      40
#define DEFAULT_MAX_MOISTURE_THRESHOLD      70
#define DEFAULT_MAX_WATERING_DURATION_SEC   60
#define DEFAULT_SENSOR_CHECK_INTERVAL_SEC   300
#define DEFAULT_MANUAL_WATERING_DURATION_SEC 10
#define DEFAULT_MAX_RANGE_TEMPERATURE 35
#define DEFAULT_MIN_RANGE_TEMPERATURE 20

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LEDState;

typedef struct {
    uint8_t  soilMoisturePercent;
    int16_t  environmentTemperature;
} SensorData;

typedef struct {
    uint8_t  minMoistureThreshold;
    uint8_t  maxMoistureThreshold;
    uint16_t maxWateringDuration;
    uint16_t sensorCheckInterval;
    SystemMode currentMode;
    uint16_t manualWateringDuration;
} SystemSettings;

extern SensorData globalSensorData;
extern SystemSettings globalSystemSettings;
extern PumpState globalPumpState;
extern LEDState globalLedState;

#endif // CONFIG_H