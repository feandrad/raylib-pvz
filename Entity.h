#pragma once

#include "raylib.h"

class Entity {
public:
    virtual ~Entity() = default;  

    virtual void Draw() const = 0;   
    virtual void Update(float deltaTime) = 0;  
};
