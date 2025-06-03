#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

typedef struct {
    void (*turnOn)();
    void (*turnOff)();
    void (*setBrightness)(int level);
} LightSystem;

LightSystem* createLightSystem();

#endif  // LIGHTING_SYSTEM_H