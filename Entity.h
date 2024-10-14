#pragma once

#include "raylib.h"
#include <vector>

enum class CollisionType {
    None,
    Point,
    Rectangle,
    Circle,
    Polygon
};

class Entity {

public:
    Vector2 position;

    virtual void Draw() const = 0;
    virtual void Update(float deltaTime) = 0;
};
