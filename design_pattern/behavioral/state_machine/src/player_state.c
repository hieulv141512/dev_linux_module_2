#include "../inc/player_state.h"
#include "../inc/music_player.h"
#include <stdlib.h>
#include <stdio.h>

// STOPPED_STATE
static void stoppedPlayButtonPressed(MusicPlayerContext* player) {
    printf("STOPPED: Playing music...\n");
    setPlayerState(player, STATE_PLAYING);
}

static void stoppedPauseButtonPressed(MusicPlayerContext* player) {
    printf("STOPPED: No music to pause.\n");
}

static void stoppedStopButtonPressed(MusicPlayerContext* player) {
    printf("STOPPED: Already stopped.\n");
}

PlayerState* createStoppedState() {
    PlayerState* stopped = (PlayerState*)malloc(sizeof(PlayerState));
    if (stopped == NULL) {
        fprintf(stderr, "STOPPED: Failed to allocate memory for stopped state instance. \n");
        return NULL;
    }

    stopped->pressPlay = stoppedPlayButtonPressed;
    stopped->pressPause = stoppedPauseButtonPressed;
    stopped->pressStop = stoppedStopButtonPressed;
    stopped->player = NULL;

    return stopped;
}

// PLAYING_STATE
static void playingPlayButtonPressed(MusicPlayerContext* player) {
    printf("PLAYING: Already playing music.\n");
}

static void playingPauseButtonPressed(MusicPlayerContext* player) {
    printf("PLAYING: Pausing music.\n");
    setPlayerState(player, STATE_PAUSED);
}

static void playingStopButtonPressed(MusicPlayerContext* player) {
    printf("PLAYING: Stopping music.\n");
    setPlayerState(player, STATE_STOPPED);
}

PlayerState* createPlayingState() {
    PlayerState* playing = (PlayerState*)malloc(sizeof(PlayerState));
    if (playing == NULL) {
        fprintf(stderr, "PLAYING: Failed to allocate memory for playing state instance. \n");
        return NULL;
    }

    playing->pressPlay = playingPlayButtonPressed;
    playing->pressPause = playingPauseButtonPressed;
    playing->pressStop = playingStopButtonPressed;
    playing->player = NULL;

    return playing;
}

// PAUSED_STATE
static void pausedPlayButtonPressed(MusicPlayerContext* player) {
    printf("PAUSED: Playing music...\n");
    setPlayerState(player, STATE_PLAYING);
}

static void pausedPauseButtonPressed(MusicPlayerContext* player) {
    printf("PAUSED: Already paused music.\n");
}

static void pausedStopButtonPressed(MusicPlayerContext* player) {
    printf("PAUSED: Stopping music.\n");
    setPlayerState(player, STATE_STOPPED);
}

PlayerState* createPausedState() {
    PlayerState* paused = (PlayerState*)malloc(sizeof(PlayerState));
    if (paused == NULL) {
        fprintf(stderr, "PAUSED: Failed to allocate memory for paused state instance. \n");
        return NULL;
    }

    paused->pressPlay = pausedPlayButtonPressed;
    paused->pressPause = pausedPauseButtonPressed;
    paused->pressStop = pausedStopButtonPressed;
    paused->player = NULL;

    return paused;
}

// void printStatus(MusicPlayerContext* player) {
//     printf("Current Player Status: %s.\n", MusicPlayerStates[player->currentState]);
// }

void setPlayerContext(PlayerState* state, MusicPlayerContext* player) {
    state->player = player;
}