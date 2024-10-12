#pragma once

#include "raylib.h"

class Zombie {
public:
    Rectangle rec;
    Color color;
    int health;
    float speed;

    Zombie();  
    Zombie(float x, float y, float speed, int health);  

    void Update(float deltaTime);  
    bool IsDead();  
};
