// All collision objects
struct CollisionObject {
    void (*collide)(void*, void*); // self, other obj
    void (*onCollide)(void*); // self
    unsigned char obj_index;
    unsigned char health;
};
typedef struct CollisionObject CollisionObject;

void collideCollisionObject (void* self, void* obj) {
    ((CollisionObject*) self)->onCollide(self);
    ((CollisionObject*) obj)->onCollide(obj);
}

void onCollideCollisionObject (void* self) {
    printf("Object %d collided!", ((CollisionObject*) self)->obj_index);
}

// Enemy
struct EnemyPlane {
    unsigned short x;
    unsigned short y;
    unsigned char health;
    unsigned char obj_index;
    void (*draw)(void*); // self
    void (*collide)(void*, void*); // self, other obj
    void (*onCollide)(void*); // self
};
typedef struct EnemyPlane EnemyPlane;

void collideEnemyPlane (void* self, void* obj) {
    printf("balin\n");
    ((CollisionObject*) self)->onCollide(*self);
    printf("sab\n");
    ((CollisionObject*) obj)->onCollide(obj);
    printf("seabass\n");
}

void onCollideEnemyPlane (void* self) {
    printf("bombur\n");
    printf("Self: %d\n", ((CollisionObject*) self)->obj_index);
}

EnemyPlane createEnemyPlane (int n, unsigned char health, unsigned short x, unsigned short y) {
    EnemyPlane temp = {
        .obj_index = n,
        .collide = *collideEnemyPlane,
    };
    return temp;
}

// Bullet
struct Bullet {
    unsigned short x;
    unsigned short y;
    unsigned char health;
    unsigned char obj_index;
    void (*draw)(void*); // self
    void (*collide)(void*, void*); // self, other obj
};
typedef struct Bullet Bullet;

void collideBullet (void* self, void* obj) {
    ((CollisionObject*) self)->onCollide(self);
    ((CollisionObject*) obj)->onCollide(obj);
}

void onCollideBullet (void* self) {
    printf("Object %d collided!", ((Bullet*) self)->obj_index);
}
