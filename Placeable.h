#pragma once

#include "raylib.h"

class Placeable {
public:
    virtual ~Placeable() = default;  

    virtual void Draw() const = 0;   
    virtual void Update(float deltaTime) = 0;  
};
