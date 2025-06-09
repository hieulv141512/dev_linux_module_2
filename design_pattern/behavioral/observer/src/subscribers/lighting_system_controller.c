#include "../../inc/subscribers/lighting_system_controller.h"
#include <stdio.h>

// Update method for LightingSystemController
void lightingSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo){
    (void)self; (void)context;
    printf("[LightingSystem] Alert: %s\n", eventInfo);
}

// Initialize LightingSystemController
void lightingSystemControllerInit(LightingSystemController* controller){
    controller->base.update = lightingSystemUpdate;
    controller->base.data = NULL;
}