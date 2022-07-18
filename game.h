
/* LIBRARIES */
#include <GL/glut.h> // for graphics

/* CONSTANTS */
unsigned short game_width = 480;
unsigned short game_height = 480;

/* UTILITY FUNCTIONS */
void placePixel (unsigned short x, unsigned short y, float r, float g, float b) {
    glutGet(GLUT_SCREEN_HEIGHT);
    glutGet(GLUT_SCREEN_WIDTH);
    x = (float)x;
    y = (float)y;
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(2.0*(((float)x/(0.5*game_width))-0.5)           ,
                   2.0*(((float)y/(0.5*game_height))-0.5)           );
        glVertex2f(2.0*(((float)x/(0.5*game_width))-0.5)+(1.0/60.0),
                   2.0*(((float)y/(0.5*game_height))-0.5)           );
        glVertex2f(2.0*(((float)x/(0.5*game_width))-0.5)+(1.0/60.0),
                   2.0*(((float)y/(0.5*game_height))-0.5)+(1.0/60.0));
        glVertex2f(2.0*(((float)x/(0.5*game_width))-0.5)           ,
                   2.0*(((float)y/(0.5*game_height))-0.5)+(1.0/60.0));
    glEnd();
}

/* DEFINE BASE OBJECTs */
// Game Object
typedef struct GameObject GameObject;
struct GameObject {
    unsigned short x;
    unsigned short y;
    unsigned char obj_index;
    unsigned char health;
    void (*draw)(GameObject*); // self
    void (*draw_hitbox)(GameObject*); // self
    void (*collide)(GameObject*, GameObject*); // self, other obj
    void (*on_collide)(GameObject*); // self
};

GameObject createGameObject (unsigned short x,
                             unsigned short y,
                             unsigned char obj_index,
                             unsigned char health,
                             void* draw,
                             void* draw_hitbox,
                             void* collide,
                             void* on_collide) {
    GameObject temp = {
        .x = x,
        .y = y,
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
void drawDummy (GameObject* self) {}

void drawHitboxDummy (GameObject* self) {}

void collideDummy (GameObject* self, GameObject* other) {}

void onCollideDummy (GameObject* self) {}

GameObject createDummy () {
    GameObject temp = {
        .x = 3,
        .y = 0,
        .obj_index = 0,
        .health = 0,
        .draw = &drawDummy,
        .draw_hitbox = &drawHitboxDummy,
        .collide = &collideDummy,
        .on_collide = &onCollideDummy,
    };
    return temp;
}

// Enemy Plane
void drawEnemyPlane (GameObject* self) {
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
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
    placePixel(self -> x+1, self -> y-7, 1.0, 0.0, 0.0);
}

void drawHitboxEnemyPlane (GameObject* self) {
    // TODO implement
}

void collideEnemyPlane (GameObject* self, GameObject* other) {
    printf("Collision from EnemyPlane object %d with object %d\n", self -> obj_index, other -> obj_index);
    self->on_collide(self);
    other->on_collide(other);
}

void onCollideEnemyPlane (GameObject* self) {
    self->health--;
    printf("EnemyPlane %d at health %d\n", self -> obj_index, self -> health);
    // TODO implement
 }

GameObject createEnemyPlane (unsigned short x,
                             unsigned short y,
                             unsigned char obj_index,
                             unsigned char health) {
    GameObject temp = {
        .x = x,
        .y = y,
        .obj_index = obj_index,
        .health = health,
        .draw = &drawEnemyPlane,
        .draw_hitbox = &drawHitboxEnemyPlane,
        .collide = &collideEnemyPlane,
        .on_collide = &onCollideEnemyPlane,
    };
    return temp;
}

// Player
typedef struct Player Player;
struct Player {
    GameObject game_object;
    int score;
    void (*take_input)(Player *);
};

void drawPlayer (GameObject* self) {
    printf("Player %d!\n", self -> obj_index);
}

void drawHitboxPlayer (GameObject* self) {
    // TODO implement
}

void collidePlayer (GameObject* self, GameObject* other) {
    printf("Collision from Player object %d with object %d\n", self -> obj_index, other -> obj_index);
    self->on_collide(self);
    other->on_collide(other);
}

void onCollidePlayer (GameObject* self) {
    self->health--;
    printf("Player %d at health %d\n", self -> obj_index, self -> health);
 }

void takeInputPlayer (Player* self) {
    // TODO implement
}

Player createPlayer (unsigned short x,
                     unsigned short y,
                     unsigned char obj_index,
                     unsigned char health) {
    Player temp = {
        .game_object = {
            .x = x,
            .y = y,
            .obj_index = obj_index,
            .health = health,
            .draw = &drawPlayer,
            .draw_hitbox = &drawHitboxPlayer,
            .collide = &collidePlayer,
            .on_collide = &onCollidePlayer,
        },
        .score = 0,
        .take_input = &takeInputPlayer,
    };
    return temp;
}
