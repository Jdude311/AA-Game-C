
#include <stdio.h>
#include <stdlib.h>

// Game header
#include "game.h"

int main(void) {
    // Initialize list for all GameObjects
    unsigned char NUM_GAME_OBJECTS = 255;
    GameObject* game_objects[NUM_GAME_OBJECTS];

    // Initialize player
    Player player = createPlayer(0, 0, 0, 10);
    game_objects[0] = &(player.game_object);

    // Initialize enemies
    unsigned char NUM_ENEMY_PLANES = 10;
    GameObject enemy_planes[NUM_ENEMY_PLANES];
    for (int i = 1; i < NUM_ENEMY_PLANES+1; i++) {
        enemy_planes[i] = createEnemyPlane(0, 0, i, 10);
        // Put object pointers in game_objects list
        game_objects[i] = &enemy_planes[i];
    }
    enemy_planes[1].collide(&enemy_planes[1], &enemy_planes[2]);
    player.game_object.collide(&(player.game_object), &enemy_planes[3]);

    return 0;
}
