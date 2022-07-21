
#include <stdio.h>
#include <stdlib.h>

// Game header
#include "game.h"

/* INITIALIZATION FOR GLUT FUNCTIONS */
// Initialize list for all GameObjects
#define NUM_GAME_OBJECTS 255
GameObject** game_objects;
// Initialize player
Player player;
// Initialize collision list
unsigned char* collision_list;

/* FUNCTION DEFINITIONS */
// Keyboard callback
void keyboard_input (unsigned char key, int x, int y) {
    printf("key %d\n", key);
    player.take_input(&player, key);
}

// Update game objects
void updateGameObjects (GameObject** game_objects, unsigned char len) {
    for (int i = 0; i < len; i++) {
        game_objects[i] -> draw_hitbox(game_objects[i], &collision_list);
        game_objects[i] -> move(game_objects[i]);
    }
}

// Idle function callback
void update () {
    updateGameObjects(game_objects, NUM_GAME_OBJECTS);
}

// Display game objects
void displayGameObjects (GameObject** game_objects, unsigned char len) {
    // TODO implement opengl display callback
    for (int i = 0; i < len; i++) {
        game_objects[i] -> draw(game_objects[i]);
    }
}

// GLUT timer function
void timer () {
    glutTimerFunc(1000/60.0, timer, 0);
    update();
    glutPostRedisplay();
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
    // Initialize collision objects list
    collision_list = malloc(sizeof(unsigned char) * game_width * game_height);
    for (int i = 0; i < game_width * game_height; i++) {
        collision_list[i] = 255;
    }

    // Initialize game objects list
    game_objects = malloc(sizeof(GameObject*) * NUM_GAME_OBJECTS+1);

    // Fill game list with dummy object
    GameObject dummy = createDummy();
    for (int i = 0; i < NUM_GAME_OBJECTS; i++) {
        game_objects[i] = &dummy;
    }

    // Initialize player
    player = createPlayer(240, 240, 0, 10);
    game_objects[0] = &(player.game_object);

    // Initialize enemies
    unsigned char NUM_ENEMY_PLANES = 10;
    GameObject enemy_planes[NUM_ENEMY_PLANES];
    for (int i = 0; i < NUM_ENEMY_PLANES; i++) {
        enemy_planes[i] = createEnemyPlane(240, 240, 0, 3, i+1, 10);
        // Put object pointers in game_objects list
        game_objects[i+1] = &enemy_planes[i];
    }

    // Graphics
    glutInit(&argc, argv);
    glutCreateWindow("The Video Game");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(0,0);
    //glutIdleFunc(&update);
    glutDisplayFunc(&display);
    glutTimerFunc(1, timer, 0);
    glutKeyboardFunc(keyboard_input);

    /* TEST CLASSES */
    enemy_planes[1].collide(&enemy_planes[1], &enemy_planes[2]);
    player.game_object.collide(&(player.game_object), &enemy_planes[3]);
    glutMainLoop();

    return 0;
}
