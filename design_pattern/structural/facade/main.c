#include <stdio.h>
#include <stdlib.h>
#include "inc/smart_home_facade.h"

int main(){
    SmartHomeFacade* smartHome = createSmartHomeFacade();
    if (smartHome == NULL) {
        return 1;
    }

    printf("\n>>> Activating morning routine...\n");
    activateMorningRoutine(smartHome);

    printf("\n>>> Activating away mode...\n");
    activateAwayMode(smartHome);

    printf("\n>>> Activating movie night scene...\n");
    setMovieNightScene(smartHome);

    printf("\nFreeing allocated memory...\n");
    free(smartHome->lighting);
    free(smartHome->hvac);
    free(smartHome->security);
    free(smartHome);

    return 0;
}