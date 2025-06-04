#ifndef HVAC_SYSTEM_H
#define HVAC_SYSTEM_H

typedef struct {
    void (*setTemperature)(int temperature);
    void (*setMode)(const char* mode);
} HvacSystem;

HvacSystem* createHvacSystem();

#endif  // HVAC_SYSTEM_H