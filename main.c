
#include <stdio.h>
#include <stdlib.h>

// Game header
#include "game.h"

int main(void) {
    // Initialize list for all GameObjects
    unsigned char NUM_GAME_OBJECTS = 256;
    GameObject* game_objects = malloc(sizeof(GameObject) * NUM_GAME_OBJECTS);

    // Initialize player
    Player player; // TODO implement player

    // Initialize enemies
    unsigned char NUM_ENEMY_PLANES = 10;
    GameObject* enemy_planes = malloc(sizeof(GameObject) * NUM_ENEMY_PLANES);
    for (int i = 1; i < NUM_ENEMY_PLANES+1; i++) {
        enemy_planes[i] = createEnemyPlane(0, 0, i, 10);
        // Put object pointers in game_objects list
        game_objects[i] = enemy_planes[i];
    }
    enemy_planes[1].collide(&enemy_planes[1], &enemy_planes[2]);

    return 0;
}
