#pragma once

#include "raylib.h"
#include "Entity.h"
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
    float lastShotTime; 

    Plant(PlantStats pStats, float x, float y); 

    bool GetHealth() const { return stats.health; } 

    bool CanShoot(float currentTime) const; 
    void Shoot(float currentTime); 
    Rectangle GetCollisionBoundary() const;

    void Draw() const override;
    void Update(float deltaTime) override;
};

static const PlantStats DEFAULT_PLANT = PlantStats(5, 1.0f, 30.0f, 70.0f);
