#pragma once

#include "raylib.h"
#include "Entity.h"

struct ZombieStats {
    float width;
    float height;
    int health;
    float speed;

    ZombieStats(float width, float height, int health, float speed)
        : width(width), height(height), health(health), speed(speed) {}
};

class Zombie : public Entity {

public:
    ZombieStats stats;
    Color color;

    Zombie(ZombieStats z, Vector2 position) : stats(z), color(RED) {
        this->position = position; 
    }

    bool IsDead() const;  
    Rectangle GetCollisionBoundary() const;
    void TakeDamage(int dmg);

    void Draw() const override;
    void Update(float deltaTime) override;
};

static const ZombieStats DEFAULT_ZOMBIE = ZombieStats(50.0f, 70.0f, 5, 15.0f);
