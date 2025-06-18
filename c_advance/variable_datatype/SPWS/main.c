#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "inc/config.h"
#include "inc/system_state.h"
#include "inc/sensors.h"
#include "inc/actuators.h"
#include "inc/buttons.h"
#include "inc/watering_logic.h"
#include "inc/notifications.h"

uint32_t getCurrentTimeSec(void) {
    return (uint32_t)time(NULL);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    systemStateInit();
    srand(getCurrentTimeSec());

    sendMessage("Smart Plant Watering System started!");

    uint32_t currentTimeSec;
    uint32_t lastDisplayTime = 0;
    const uint32_t displayIntervalSec = 5;

    char inputChar;

    while(1) {
        currentTimeSec = getCurrentTimeSec();
        printf("Press 'm' to toggle mode, 'w' for manual water, 'q' to quit: \n");
        
        scanf("%c", &inputChar);
        if (inputChar == 'm' || inputChar == 'M') {
            pressSwitchModeButton();
        } else if (inputChar == 'w' || inputChar == 'W') {
            pressManualWateringButton();
        } else if (inputChar == 'q' || inputChar == 'Q') {
            sendMessage("Exiting system.");
            break;
        }

        if (globalSystemSettings.currentMode == MODE_AUTO) {
            handleWateringAutoMode(currentTimeSec);
        } 
        else {
            handleWateringManual(currentTimeSec);
            if (!globalIsManualWateringActive) {
                setLedState(LED_NORMAL);
            }
        }

        if ((currentTimeSec - lastDisplayTime) >= displayIntervalSec) {
            clearScreen();
            sendStatus();
            lastDisplayTime = currentTimeSec;
        }
        
        sleep(1);
    }

    return 0;
}