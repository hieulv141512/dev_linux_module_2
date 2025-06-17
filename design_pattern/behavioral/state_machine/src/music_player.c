#include "../inc/music_player.h"
#include <stdlib.h>
#include <stdio.h>

MusicPlayerContext* createMusicPlayerContext(PlayerState* initState) {
    MusicPlayerContext* player = (MusicPlayerContext*)malloc(sizeof(MusicPlayerContext));
    if (player == NULL) {
        fprintf(stderr, "Music Player: Failed to allocate memory for MusicPlayerContext instance.\n");
        return NULL;
    }

    player->currentState = STATE_STOPPED;
    player->currentStateHandler = initState;
    
    return player;
}

void destroyMusicPlayerContext(MusicPlayerContext* player) {
    if (player != NULL) {
        free(player->currentStateHandler);
        free(player);
    }
}