
#include <stdio.h>
#include <stdlib.h>

// Game header
#include "game.h"

/* INITIALIZATION FOR GLUT FUNCTIONS */
// Initialize list for all GameObjects
//#define NUM_GAME_OBJECTS 255
GameObject** game_objects;
// Initialize player
Player player;
// Initialize collision list
unsigned char* collision_list;

/* FUNCTION DEFINITIONS */
// Keyboard callback
/* void keyboard_input (unsigned char key, int x, int y) { */
/*     player.input(&player, key); */
/* } */

// Update game objects
/* void updateGameObjects (GameObject** game_objects, unsigned char len) { */
/*     for (int i = 0; i < len; i++) { */
/*         game.game_objects[i] -> draw_hitbox(game_objects[i], &collision_list); */
/*         game.game_objects[i] -> move(game.game_objects[i]); */
/*     } */
/* } */

// Idle function callback
/* void update () { */
/*     updateGameObjects(game_objects, NUM_GAME_OBJECTS); */
/* } */

// Display game objects
/* void displayGameObjects (GameObject** game_objects, unsigned char len) { */
/* } */

// GLUT timer function
void timer () {
    glutTimerFunc(1000/60.0, timer, 0);
    game.update();
    glutPostRedisplay();
}

// GLUT display callback
/* void display () { */
/*     // Prepare to draw */
/*     glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background color */
/*     glClear(GL_COLOR_BUFFER_BIT); // clear color buffer */

/*     // Display game items */
/*     displayGameObjects(game.game_objects, NUM_GAME_OBJECTS); */

/*     // Finalize frame */
/*     glFlush(); // render */
/* } */

// Driver function
int main (int argc, char** argv) {
    /* SETUP */
    // Initialize collision objects list
    game.collision_list = malloc(sizeof(unsigned char) * game_width * game_height);
    for (int i = 0; i < game_width * game_height; i++) {
        game.collision_list[i] = 255;
    }

    // Initialize game objects list
    game.game_objects = malloc(sizeof(GameObject*) * NUM_GAME_OBJECTS+1);


    // Fill game list with dummy object
    game.dummy = createDummy();
    for (int i = 0; i <= NUM_GAME_OBJECTS; i++) {
        game.game_objects[i] = &game.dummy;
    }

    // Initialize player
    game.player = createPlayer(game_width/2, 0, 0, 10);
    game.game_objects[0] = &(game.player.game_object);

    // Initialize enemies
    unsigned char NUM_ENEMY_PLANES = 20;
    GameObject enemy_planes[NUM_ENEMY_PLANES];
    for (int i = 0; i < NUM_ENEMY_PLANES; i++) {
        enemy_planes[i] = createEnemyPlane(
            rand() % game_width,
            rand() % 300 + game_height - 300,
            rand() % 360,
            rand() % 4+2,
            i+1,
            10);
        // Put object pointers in game_objects list
        game.game_objects[i+1] = &enemy_planes[i];
        game.game_objects[i+1] -> move(game.game_objects[i+1]);
    }

    // Graphics
    glutInit(&argc, argv);
    glutCreateWindow("The Video Game");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(0,0);
    //glutIdleFunc(&update);
    glutDisplayFunc(game.display);
    glutTimerFunc(1, timer, 0);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(game.keyboard_down);
    glutKeyboardUpFunc(game.keyboard_up);
    glutPassiveMotionFunc(game.update_mouse);
    /* glutKeyboardFunc(game.input); */

    /* TEST CLASSES */
    glutMainLoop();

    return 0;
}
