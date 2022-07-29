
/* LIBRARIES */
#include <GL/glut.h> // for graphics
#include <math.h> // for math
#include <stdbool.h> // booleans, duh

/* CONSTANTS */
unsigned short game_width = 480;
unsigned short game_height = 480;

#define NUM_GAME_OBJECTS 255

#define PI 3.141592654


/* UTILITY FUNCTIONS */
void placePixel (float x, float y, float r, float g, float b) {
    glutGet(GLUT_SCREEN_HEIGHT);
    glutGet(GLUT_SCREEN_WIDTH);
    x = (float)x;
    y = (float)y;
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(2.0*(((float)x/(1.0*game_width))-0.5)                         ,
                   2.0*(((float)y/(1.0*game_height))-0.5)                        );
        glVertex2f(2.0*(((float)x/(1.0*game_width))-0.5)+(1.0/(game_width/4.0))  ,
                   2.0*(((float)y/(1.0*game_height))-0.5)                        );
        glVertex2f(2.0*(((float)x/(1.0*game_width))-0.5)+(1.0/(game_width/4.0))  ,
                   2.0*(((float)y/(1.0*game_height))-0.5)+(1.0/(game_height/4.0)));
        glVertex2f(2.0*(((float)x/(1.0*game_width))-0.5)                         ,
                   2.0*(((float)y/(1.0*game_height))-0.5)+(1.0/(game_height/4.0)));
    glEnd();
}

/* DEFINE BASE OBJECTS */
// Struct Definitions
typedef struct GameObject GameObject;
struct GameObject {
    char type;
    float x;
    float y;
    float angle;
    float velocity;
    unsigned char obj_index;
    unsigned char health;
    void (*move)(GameObject*); //self
    void (*draw)(GameObject*); // self
    void (*draw_hitbox)(GameObject*, unsigned char*); // self, collision list--used internally
    void (*check_collisions)(GameObject*); // self
    void (*collide)(GameObject*, GameObject*); // self, other obj
    void (*on_collide)(GameObject*); // self
};

typedef struct Player Player;
struct Player {
    GameObject game_object;
    int score;
    void (*input)(Player *, bool*);
};


// Game (methods for full game and global game variables)
struct Game {
    // Global variables
    GameObject** game_objects;
    unsigned char* collision_list;
    bool pressed_keys[255];
    Player player;

    // GL callback functions
    void (*update)(void);
    void (*display)(void);
    void (*timer)(void);
    void (*keyboard_up)(unsigned char key, int x, int y);
    void (*keyboard_down)(unsigned char key, int x, int y);
};
struct Game game;

void update () {
    for (int i = 0; i < game_width * game_height; i++) {
        game.collision_list[i] = 255;
    }

    for (int i = 0; i < NUM_GAME_OBJECTS; i++) {
        game.game_objects[i] -> check_collisions(game.game_objects[i]);
        game.game_objects[i] -> move(game.game_objects[i]);
    }
    game.player.input(&game.player, game.pressed_keys);
}

void display () {
    // Prepare to draw
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background color
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer

    // Display game items
    for (int i = 0; i < NUM_GAME_OBJECTS; i++) {
        game.game_objects[i] -> draw(game.game_objects[i]);
    }

    // Finalize frame
    glFlush(); // render
}

void keyboardUp (unsigned char key, int x, int y) {
    game.pressed_keys[key] = false;
    game.player.input(&game.player, game.pressed_keys);
}

void keyboardDown (unsigned char key, int x, int y) {
    game.pressed_keys[key] = true;
    game.player.input(&game.player, game.pressed_keys);
}

struct Game game = (struct Game) {
    .update = update,
    .display = display,
    .keyboard_down = keyboardDown,
    .keyboard_up = keyboardUp,
};

// Game Object
GameObject createGameObject (char type,
                             float x,
                             float y,
                             float angle,
                             char velocity,
                             unsigned char obj_index,
                             unsigned char health,
                             void* draw,
                             void* draw_hitbox,
                             void* collide,
                             void* on_collide) {
    GameObject temp = {
        .type = type,
        .x = x,
        .y = y,
        .angle = angle,
        .velocity = velocity,
        .obj_index = obj_index,
        .health = health,
        .draw = draw,
        .draw_hitbox = draw_hitbox,
        .collide = collide,
        .on_collide = on_collide,
    };
    return temp;
}

/* DEFINE OBJECTS */
// Dummy object
void moveDummy (GameObject* self) {}

void drawDummy (GameObject* self) {}

void drawHitboxDummy (GameObject* self, unsigned char* collision_list) {}

void checkCollisionsDummy (GameObject* self) {}

void collideDummy (GameObject* self, GameObject* other) {}

void onCollideDummy (GameObject* self) {}

GameObject createDummy () {
    GameObject temp = {
        .type = -1,
        .x = 3,
        .y = 0,
        .angle = 0,
        .velocity = 0,
        .obj_index = 255,
        .health = 0,
        .move = &moveDummy,
        .draw = &drawDummy,
        .check_collisions = &checkCollisionsDummy,
        .collide = &collideDummy,
        .on_collide = &onCollideDummy,
    };
    return temp;
}

// Enemy Plane
void moveEnemyPlane (GameObject* self) {
    if (self -> health == 0) return;
    self -> angle += (((rand()%100)/100.0) - 0.5);
    self -> x += self -> velocity * cos(self -> angle * PI / 180);
    self -> y += self -> velocity * sin(self -> angle * PI / 180);
    if (self -> x > game_width) {
        self -> x -= game_width;
    } else if (self -> x < 0) {
        self -> x += game_width;
    }
    if (self -> y > game_height) {
        self -> y -= game_height;
    } else if (self -> y < 0) {
        self -> y += game_height;
    }
}

void drawEnemyPlane (GameObject* self) {
    if (self -> health == 0) return;
    // Vertical E
    placePixel(self -> x  , self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-1, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-2, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-4, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-5, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-6, 1.0, 0.0, 0.0);
    placePixel(self -> x  , self -> y-7, 1.0, 0.0, 0.0);

    // Top E
    placePixel(self -> x+1, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+2, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+3, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+4, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+5, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+6, self -> y  , 1.0, 0.0, 0.0);
    placePixel(self -> x+7, self -> y  , 1.0, 0.0, 0.0);

    // Middle E
    placePixel(self -> x+1, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+2, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+3, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+4, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+5, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+6, self -> y-3, 1.0, 0.0, 0.0);
    placePixel(self -> x+7, self -> y-3, 1.0, 0.0, 0.0);

    // Bottom E
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+2, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+3, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+4, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+5, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+6, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+7, self -> y-7, 1.0, 0.0, 0.0);
}

void checkCollisionsEnemyPlane (GameObject* self) {
    if (self -> health == 0) return;
    bool check = true;
    int i = 0;
    for (int xx = 0; xx < 8; xx++) {
        for (int yy = 0; yy < 8; yy++) {
            i = game_width * (self -> y + yy) + (self -> x + xx);
            if (i < 0 || xx + self -> x > game_width || yy + self -> y > game_height) break;
            if (check &&
             game.game_objects[game.collision_list[i]] -> type != self -> type &&
             game.game_objects[game.collision_list[i]] -> type >= 0 &&
             game.collision_list[i] != self -> obj_index) {
                printf("balls %f %f\n", self -> x, self -> y);
                check = false;
                /* self -> collide(self, game.game_objects[game.collision_list[i]]); */
            }
            game.collision_list[i] = self -> obj_index;
        }
    }
}

void collideEnemyPlane (GameObject* self, GameObject* other) {
    printf("Collision from EnemyPlane object %d with object %d\n", self -> obj_index, other -> obj_index);
    self->on_collide(self);
    other->on_collide(other);
}

void onCollideEnemyPlane (GameObject* self) {
    if (self -> health > 0) self -> health--;
    printf("EnemyPlane %d at health %d\n", self -> obj_index, self -> health);
    // TODO implement
 }

GameObject createEnemyPlane (float x,
                             float y,
                             float angle,
                             float velocity,
                             unsigned char obj_index,
                             unsigned char health) {
    GameObject temp = {
        .type = 1,
        .x = x,
        .y = y,
        .angle = angle,
        .velocity = velocity,
        .obj_index = obj_index,
        .health = health,
        .move = &moveEnemyPlane,
        .draw = &drawEnemyPlane,
        .check_collisions = &checkCollisionsEnemyPlane,
        .collide = &collideEnemyPlane,
        .on_collide = &onCollideEnemyPlane,
    };
    return temp;
}

// Player
void movePlayer (GameObject* self) {
    self -> x += self -> velocity * cos(self -> angle * PI / 180);
    self -> y += self -> velocity * sin(self -> angle * PI / 180);
    if (self -> x > game_width) {
        self -> x -= game_width;
    } else if (self -> x < 0) {
        self -> x += game_width;
    }
    if (self -> y > game_height) {
        self -> y -= game_height;
    } else if (self -> y < 0) {
        self -> y += game_height;
    }
}

void drawPlayer (GameObject* self) {
    for (int xx = 0; xx < 8; xx++) {
        for (int yy = 0; yy < 8; yy++) {
            placePixel(self -> x + xx, self -> y + yy, 0.0, 0.0, 1.0);
        }
    }
}

void checkCollisionsPlayer (GameObject* self) {
    bool check = true;
    int i = 0;
    for (int xx = 0; xx < 8; xx++) {
        for (int yy = 0; yy < 8; yy++) {
            i = game_width * (self -> y + yy) + (self -> x + xx);
            if (i < 0 || xx + self -> x > game_width || yy + self -> y > game_height) break;
            if (check &&
             game.collision_list[i] != 255 &&
             game.collision_list[i] != self -> obj_index) {
                check = false;
                self -> collide(self, game.game_objects[game.collision_list[i]]);
            }
            game.collision_list[i] = self -> obj_index;
        }
    }
}

void collidePlayer (GameObject* self, GameObject* other) {
    printf("Collision from Player object %d with object %d\n", self -> obj_index, other -> obj_index);
    self->on_collide(self);
    other->on_collide(other);
}

void onCollidePlayer (GameObject* self) {
    game.player.score++;
    printf("Player %d score %d!!!\n", self -> obj_index, game.player.score);
}

void inputPlayer (Player* self, bool* pressed_keys) {
    for (unsigned char key = 0; key < 255; key++) {
        switch (key * pressed_keys[key]) {
            case 97: // A
                self -> game_object.angle += 5;
                break;
            case 100: // D
                self -> game_object.angle -= 5;
                break;
            case 119: // W
                self -> game_object.velocity += 0.1;
                if (self -> game_object.velocity > 10)
                    self -> game_object.velocity = 10;
                break;
            case 115: // S
                self -> game_object.velocity -= 0.1;
                if (self -> game_object.velocity < 0)
                    self -> game_object.velocity = 0;
                break;
        }
    }
}

Player createPlayer (unsigned short x,
                     unsigned short y,
                     unsigned char obj_index,
                     unsigned char health) {
    Player temp = {
        .game_object = {
            .type = 0,
            .x = x,
            .y = y,
            .obj_index = obj_index,
            .health = health,
            .move = &movePlayer,
            .draw = &drawPlayer,
            /* .draw_hitbox = &drawHitboxPlayer, */
            .check_collisions = checkCollisionsPlayer,
            .collide = &collidePlayer,
            .on_collide = &onCollidePlayer,
        },
        .score = 0,
        .input = &inputPlayer,
    };
    return temp;
}
