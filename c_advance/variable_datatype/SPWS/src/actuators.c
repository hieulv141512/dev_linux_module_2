#include "actuators.h"
#include <stdio.h>

void turnPumpOn(void) {
    if (globalPumpState == PUMP_OFF) {
        globalPumpState = PUMP_ON;
        printf("[ACTUATORS] PUMP ON\n");
    }
}

void turnPumpOff(void) {
    if (globalPumpState == PUMP_ON) {
        globalPumpState = PUMP_OFF;
        printf("[ACTUATORS] PUMP OFF\n");
    }
}

void setLedState(LEDState state) {
    if (globalLedState != state) {
        globalLedState = state;
        switch (globalLedState) {
            case LED_NORMAL:
                printf("[ACTUATORS] LED State: GREEN (Normal)\n");
                break;
            case LED_WATERING:
                printf("[ACTUATORS] LED State: YELLOW (Watering)\n");
                break;
            case LED_LOW_MOISTURE_ALERT:
                printf("[ACTUATORS] LED State: BLUE (Low Moisture Alert)\n");
                break;
            case LED_ERROR:
                printf("[ACTUATORS] LED State: RED (Error)\n");
                break;
            default:
                break;
        }
    }
}