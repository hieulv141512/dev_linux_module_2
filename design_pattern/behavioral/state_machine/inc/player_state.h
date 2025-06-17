#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "music_player.h"

typedef struct PlayerState {
    void (*pressPlay)(MusicPlayerContext* player);
    void (*pressStop)(MusicPlayerContext* player);
    void (*pressPause)(MusicPlayerContext* player);
} PlayerState;

PlayerState* createStoppedState();
PlayerState* createPlayingState();
PlayerState* createPausedState();
void setPlayerState(MusicPlayerContext* player, MusicPlayerState newState);

#endif // PLAYER_STATE_H