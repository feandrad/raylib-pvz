#pragma once

#include "raylib.h"
#include "Entity.h"
#include "Zombie.h"

struct ProjectileStats {
    float speed;
    float radius;

    ProjectileStats(float speed, float radius)
        : speed(speed), radius(radius) {}
};

class Projectile : public Entity {
public:
    bool isActive;
    ProjectileStats stats;
    Color color;

    Projectile(ProjectileStats stats, Vector2 position) : stats(stats), color(YELLOW) {
        this->position = position;
    }

    void Update(float deltaTime) override;
    void Draw() const override;
    void OnCollision(Entity* other);
};

static const ProjectileStats DEFAULT_PROJECTILE = ProjectileStats(500.0f, 5.0f);
