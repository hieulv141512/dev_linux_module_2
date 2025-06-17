#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

typedef enum {
    STATE_STOPPED,
    STATE_PLAYING,
    STATE_PAUSED
} MusicPlayerState;

typedef struct PlayerState PlayerState;

typedef struct MusicPlayerContext {
    MusicPlayerState currentState;
    PlayerState* currentStateHandler;
} MusicPlayerContext;

MusicPlayerContext* createMusicPlayerContext(PlayerState* initState);

void destroyMusicPlayerContext(MusicPlayerContext* player);

#endif // MUSIC_PLAYER_H