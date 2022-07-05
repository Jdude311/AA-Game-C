#include <stdio.h>

// Game header
#include "game.h"


int main(void) {
    printf("balls\n");
    EnemyPlane a = createEnemyPlane(0, 10, 0, 0);
    EnemyPlane b = createEnemyPlane(1, 10, 0, 0);
    printf("basdf\n");
    a.collide(&a, &b);
    printf("based\n");
    return 0;
}