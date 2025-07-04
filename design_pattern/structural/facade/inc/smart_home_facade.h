#ifndef SMART_HOME_FACADE_H
#define SMART_HOME_FACADE_H

#include "lighting_system.h"
#include "hvac_system.h"
#include "security_system.h"

typedef struct {
    LightSystem* lighting;
    SecuritySystem* security;
    HvacSystem* hvac;
} SmartHomeFacade;

SmartHomeFacade* createSmartHomeFacade();
void activateMorningRoutine(SmartHomeFacade* facade);
void activateAwayMode(SmartHomeFacade* facade);
void setMovieNightScene(SmartHomeFacade* facade);

#endif  //SMART_HOME_FACADE_H