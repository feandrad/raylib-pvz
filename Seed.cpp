#include "Seed.h"

Seed::Seed(float x, float y, Plant* plantToTransform) 
    : rec{x, y, 80, 80}, color(ORANGE), incubationTime(5.0f), elapsedTime(0.0f), plant(plantToTransform) {}

void Seed::Draw() const {
    float centerX = rec.x + rec.width / 2;
    float centerY = rec.y + rec.height / 2;

    DrawCircle(centerX, centerY, 30, color);  
}

void Seed::Update(float deltaTime) {
    if (elapsedTime < incubationTime) {
        elapsedTime += deltaTime; 
    } 
}
