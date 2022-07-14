
#include <stdio.h>
#include <stdlib.h>

// Game header
#include "game.h"

/* INITIALIZATION FOR GLUT FUNCTIONS */
// Initialize list for all GameObjects
#define NUM_GAME_OBJECTS 255
GameObject** game_objects[NUM_GAME_OBJECTS];

/* FUNCTION DEFINITIONS */
// Display game objects
void displayGameObjects (GameObject** game_objects, unsigned char len) {
    // TODO implement opengl display callback
    for (unsigned long i = 0; i < len; i++) {
        printf("%d\n", (game_objects[i]) -> obj_index);
        game_objects[i] -> draw(game_objects[i]);
    }
}
// GLUT display callback
void display () {
    // Prepare to draw
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background color
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer

    // Display game items
    displayGameObjects(game_objects, NUM_GAME_OBJECTS);

    // Finalize frame
    glFlush(); // render
}

// Driver function
int main (int argc, char** argv) {
    /* SETUP */
    // Graphics
    glutInit(&argc, argv);
    glutCreateWindow("The Video Game");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(0,0);
    glutDisplayFunc(display);

    // Fill game list with dummy object
    GameObject dummy = createDummy();
    for (int i = 0; i < NUM_GAME_OBJECTS; i++) {
        printf("%d\n", i);
        game_objects[i] = &dummy;
    }

    // Initialize player
    Player player = createPlayer(0, 0, 0, 10);
    game_objects[0] = &(player.game_object);

    // Initialize enemies
    unsigned char NUM_ENEMY_PLANES = 10;
    GameObject enemy_planes[NUM_ENEMY_PLANES];
    for (int i = 1; i < NUM_ENEMY_PLANES+1; i++) {
        enemy_planes[i] = createEnemyPlane(10, 10, i, 10);
        // Put object pointers in game_objects list
        game_objects[i] = &enemy_planes[i];
    }

    /* TEST CLASSES */
    enemy_planes[1].collide(&enemy_planes[1], &enemy_planes[2]);
    player.game_object.collide(&(player.game_object), &enemy_planes[3]);
    glutMainLoop();

    return 0;
}
