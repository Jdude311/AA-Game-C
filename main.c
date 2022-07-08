#include <stdio.h>

// Game header
#include "game.h"

int main(void) {
    unsigned char NUM_ENEMY_PLANES = 10;
    GameObject* enemy_planes = malloc(sizeof(GameObject) * NUM_ENEMY_PLANES);
    for (int i = 0; i < NUM_ENEMY_PLANES; i++) {
        enemy_planes[i] = createEnemyPlane(0, 0, i, 10);
    }
    enemy_planes[1].collide(&enemy_planes[1], &enemy_planes[2]);
    return 0;
}
