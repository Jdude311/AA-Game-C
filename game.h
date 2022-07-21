
/* LIBRARIES */
#include <GL/glut.h> // for graphics
#include <math.h> // for math

/* CONSTANTS */
unsigned short game_width = 480;
unsigned short game_height = 480;

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

/* DEFINE BASE OBJECTs */
// Game Object
typedef struct GameObject GameObject;
struct GameObject {
    float x;
    float y;
    float angle;
    unsigned char velocity;
    unsigned char obj_index;
    unsigned char health;
    void (*move)(GameObject*); //self
    void (*draw)(GameObject*); // self
    void (*draw_hitbox)(GameObject*, unsigned char*); // self
    void (*collide)(GameObject*, GameObject*); // self, other obj
    void (*on_collide)(GameObject*); // self
};

GameObject createGameObject (float x,
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

void collideDummy (GameObject* self, GameObject* other) {}

void onCollideDummy (GameObject* self) {}

GameObject createDummy () {
    GameObject temp = {
        .x = 3,
        .y = 0,
        .angle = 0,
        .velocity = 0,
        .obj_index = 0,
        .health = 0,
        .move = &moveDummy,
        .draw = &drawDummy,
        .draw_hitbox = &drawHitboxDummy,
        .collide = &collideDummy,
        .on_collide = &onCollideDummy,
    };
    return temp;
}

// Enemy Plane
void moveEnemyPlane (GameObject* self) {
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

void drawHitboxEnemyPlane (GameObject* self, unsigned char* collision_list) {
    // TODO implement
    for (int xx = 0; xx < 8; xx++) {
        for (int yy = 0; yy < 8; yy++) {
            collision_list[game_height * yy + xx] = self -> obj_index;
        }
    }
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

GameObject createEnemyPlane (float x,
                             float y,
                             float angle,
                             char velocity,
                             unsigned char obj_index,
                             unsigned char health) {
    GameObject temp = {
        .x = x,
        .y = y,
        .angle = angle,
        .velocity = velocity,
        .obj_index = obj_index,
        .health = health,
        .move = &moveEnemyPlane,
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
    void (*take_input)(Player *, int);
};

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

void drawHitboxPlayer (GameObject* self, unsigned char* collision_list) {
    // TODO implement
    for (int xx = 0; xx < 8; xx++) {
        for (int yy = 0; yy < 8; yy++) {
            collision_list[game_height * yy + xx] = self -> obj_index;
        }
    }
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

void takeInputPlayer (Player* self, int key) {
    // TODO implement
    switch (key) {
        case 97: // A
            self -> game_object.angle += 10;
            break;
        case 100: // D
            self -> game_object.angle -= 10;
            break;
        case 119: // W
            if (self -> game_object.velocity < 10)
                self -> game_object.velocity++;
            break;
        case 115: // S
            if (self -> game_object.velocity > 0)
                self -> game_object.velocity--;
            break;
    }

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
            .move = &movePlayer,
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
