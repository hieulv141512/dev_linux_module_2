#include "../inc/buttons.h"
#include "../inc/system_state.h"
#include "../inc/notifications.h"
#include "../inc/actuators.h"
#include <stdio.h>
#include <time.h>

void pressSwitchModeButton() {
    if (globalSystemSettings.currentMode == MODE_AUTO) {
        globalSystemSettings.currentMode = MODE_MANUAL;
        turnPumpOff();
        globalIsManualWateringActive = false;
        sendMessage("Switched to MANUAL Mode \n");
    }
    else {
        globalSystemSettings.currentMode = MODE_AUTO;
        sendMessage("Switched to AUTO Mode \n");
    }
}

void pressManualWateringButton() {
    if (globalSystemSettings.currentMode == MODE_MANUAL && !globalIsManualWateringActive) {
        globalIsManualWateringActive = true;
        time_t startTime, endTime;
        double elapsedSeconds;

        turnPumpOn();
        sendMessage("Starting manual watering.");
        startTime = time(&startTime);
        while (true) {
            endTime = time(&endTime);
            elapsedSeconds = difftime(endTime, startTime);
            if (elapsedSeconds > DEFAULT_MANUAL_WATERING_DURATION_SEC) {
                turnPumpOff();
                sendMessage("Finished manual watering.");
                break;
            }
        }
    }
    else if (globalSystemSettings.currentMode == MODE_AUTO) {
        sendMessage("Manual watering only available in MANUAL mode.");
    } 
    else if (globalIsManualWateringActive) {
        sendMessage("Manual watering already active.");
    }
}