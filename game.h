
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
// Enemy Plane
void drawEnemyPlane (GameObject* self) {
    printf("EnemyPlane %d!\n", self -> obj_index);
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
    printf("EnemyPlane %d at health %d\n", self -> obj_index, self -> health);
    // TODO implement
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
}
