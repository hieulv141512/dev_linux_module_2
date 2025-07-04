#include "../inc/lighting_system.h"
#include <stdio.h>
#include <stdlib.h>

void turnOn() {
    printf("Lighting: Turned on the light.\n");
}

void turnOff() {
    printf("Lighting: Turned off the light.\n");
}

void setBrightness(int level) {
    printf("Lighting: Set brightness to level %d.\n", level);
}

LightSystem* createLightSystem() {
    LightSystem* system = (LightSystem*)malloc(sizeof(LightSystem));
    if (system == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for Lighting System instance.\n");
        return NULL;
    }

    system->turnOn = turnOn;
    system->turnOff = turnOff;
    system->setBrightness = setBrightness;

    return system;
}