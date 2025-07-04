#include "../inc/smart_home_facade.h"
#include <stdlib.h>
#include <stdio.h>

SmartHomeFacade* createSmartHomeFacade() {
    SmartHomeFacade* facade = (SmartHomeFacade*)malloc(sizeof(SmartHomeFacade));
    if (facade == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for SmartHomeFacade instance.\n");
        return NULL;
    }

    facade->lighting = createLightSystem();
    facade->security = createSecuritySystem();
    facade->hvac = createHvacSystem();

    return facade;
}

void activateMorningRoutine(SmartHomeFacade* facade) {
    if (facade != NULL) {
        printf("Facade: Set morning routine.\n");
        facade->security->deactivateAlarm();
        facade->hvac->setTemperature(26);
    }
}

void activateAwayMode(SmartHomeFacade* facade) {
    if (facade != NULL) {
        printf("Facade: Set away mode.\n");
        facade->security->activateAlarm();
        facade->lighting->turnOff();
    }
}

void setMovieNightScene(SmartHomeFacade* facade) {
    if (facade != NULL) {
        printf("Facade: Set movie night scene.\n");
        facade->hvac->setTemperature(24);
        facade->lighting->setBrightness(4);
        facade->security->deactivateAlarm();
    }
}