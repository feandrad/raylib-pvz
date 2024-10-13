#pragma once

#include "raylib.h"
#include "Entity.h"

class Zombie : Entity {
public:
    Rectangle rec;
    Color color;
    int health;
    float speed;

    Zombie();  
    Zombie(float x, float y, float speed, int health);  

    bool IsDead();  

    void Draw() const override;
    void Update(float deltaTime) override;
};
