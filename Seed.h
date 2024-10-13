#pragma once

#include "raylib.h"
#include "Placeable.h"
#include "Plant.h"

class Seed : public Placeable {
public:
    Rectangle rec;   // Rectangle for seed dimensions
    Color color = ORANGE;     

    float incubationTime; // Time in seconds to wait before transforming
    float elapsedTime;    // Elapsed time since the seed was planted
    Plant* plant;         // Pointer to the Plant it will become

    Seed(float x, float y); 

    void Draw() const override;
    void Update(float deltaTime) override;
};
