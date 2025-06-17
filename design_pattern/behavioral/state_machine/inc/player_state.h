#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

typedef struct MusicPlayerContext MusicPlayerContext;

typedef struct PlayerState {
    MusicPlayerContext* player;
    void (*pressPlay)(MusicPlayerContext* player);
    void (*pressStop)(MusicPlayerContext* player);
    void (*pressPause)(MusicPlayerContext* player);
} PlayerState;

PlayerState* createStoppedState();
PlayerState* createPlayingState();
PlayerState* createPausedState();
// void printStatus(MusicPlayerContext* player);
void setPlayerContext(PlayerState* state, MusicPlayerContext* player);

#endif // PLAYER_STATE_H