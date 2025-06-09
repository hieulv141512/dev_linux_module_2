#ifndef LIGHTING_SYSTEM_CONTROLLER_H
#define LIGHTING_SYSTEM_CONTROLLER_H

#include "../subscriber.h"

typedef struct {
    Subscriber base;
} LightingSystemController;

void lightingSystemControllerInit(LightingSystemController* controller);

#endif // LIGHTING_SYSTEM_CONTROLLER_H