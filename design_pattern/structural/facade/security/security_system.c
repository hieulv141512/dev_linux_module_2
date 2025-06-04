#include "security_system.h"
#include <stdio.h>
#include <stdlib.h>

void activateAlarm(){
    printf("Security: Activated alarm.\n");
}

void deactivateAlarm(){
    printf("Security: Deactivated alarm.\n");
}

void monitorSensors(){
    printf("Security: Monitoring sensors.\n");
}

SecuritySystem* createSecuritySystem(){
    SecuritySystem* system = (SecuritySystem*)malloc(sizeof(SecuritySystem));
    if (system == NULL){
        fprintf(stderr, "Error: Failed to allocate memory for Security System instance.\n");
        return NULL;
    }

    system->activateAlarm = activateAlarm;
    system->deactivateAlarm = deactivateAlarm;
    system->monitorSensors = monitorSensors;
    
    return system;
}