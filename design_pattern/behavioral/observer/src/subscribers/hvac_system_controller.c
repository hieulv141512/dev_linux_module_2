#include "../../inc/subscribers/hvac_system_controller.h"
#include <stdio.h>

// Update method for HvacSystemController
void hvacSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self; (void)context;
    printf("[HvacSystem] Alert: %s\n", eventInfo);
}

// Initialize HvacSystemController
void hvacSystemControllerInit(HvacSystemController* controller) {
    controller->base.update = hvacSystemUpdate;
    controller->base.data = NULL;
}