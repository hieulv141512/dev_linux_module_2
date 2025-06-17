#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "player_state.h"

typedef enum {
    STATE_STOPPED,
    STATE_PLAYING,
    STATE_PAUSED
} MusicPlayerState;

const char* MusicPlayerStates[] = {
    "STOPPED",
    "PLAYING",
    "PAUSED"
};

typedef struct MusicPlayerContext {
    MusicPlayerState currentState;
    PlayerState* currentStateHandler;
} MusicPlayerContext;

MusicPlayerContext* createMusicPlayerContext(PlayerState* initState);
void setPlayerState(MusicPlayerContext* player, MusicPlayerState newState);
void destroyMusicPlayerContext(MusicPlayerContext* player);

#endif // MUSIC_PLAYER_H