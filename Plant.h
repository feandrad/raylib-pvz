#pragma once

#include "raylib.h"
#include "Entity.h"
#include "Projectile.h"
#include <vector>

struct PlantStats {
    int health;
    float fireRate;
    float width;
    float height;

    PlantStats(int health, float fireRate, float width, float height)
        : health(health), fireRate(fireRate), width(width), height(height) {}
};

class Plant : public Entity {
private:
    PlantStats stats; 
    Color color;

public:
    float attackCooldown; 

    Plant(PlantStats pStats, float x, float y) : stats(pStats), attackCooldown(0.0f), color(GREEN) {
        this->position = {x, y};
    }

    bool GetHealth() const { return stats.health; } 

    bool CanAttack() const; 
    Projectile* Attack(); 
    Rectangle GetCollisionBoundary() const;

    void Draw() const override;
    void Update(float deltaTime) override;
};

static const PlantStats DEFAULT_PLANT = PlantStats(5, 1.0f, 30.0f, 70.0f);
