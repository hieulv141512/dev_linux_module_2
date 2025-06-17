#include "inc/music_player.h"

int main() {
    MusicPlayerContext* player = createMusicPlayerContext(createStoppedState());

    // Simulate user interactions
    player->currentStateHandler->pressStop(player);  // Stop
    player->currentStateHandler->pressPlay(player);   // Start playing
    player->currentStateHandler->pressPause(player);  // Pause
    player->currentStateHandler->pressPlay(player);   // Resume
    player->currentStateHandler->pressStop(player);   // Stop
    player->currentStateHandler->pressPause(player);   // Try to pause when stopped
    player->currentStateHandler->pressStop(player);   // Try to stop when already stopped

    destroyMusicPlayerContext(player);

    return 0;
}