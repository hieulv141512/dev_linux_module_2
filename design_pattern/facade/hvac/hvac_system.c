#include "hvac_system.h"
#include <stdlib.h>
#include <stdio.h>


void setTemperature(int temperature){
    printf("HVAC: Set temperature to %d °C.\n", temperature);
}

void setMode(const char* mode){
    printf("HVAC: Set mode to %s.\n", mode);
}


HvacSystem* createHvacSystem(){
    HvacSystem* system = (HvacSystem*)malloc(sizeof(HvacSystem));
    if (system == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for HVAC system instance.\n");
        return NULL;
    }

    system->setTemperature = setTemperature;
    system->setMode = setMode;

    return system;
}