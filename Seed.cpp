#include "Seed.h"

Seed::Seed(float x, float y) : rec{x, y, 80, 80}, color(ORANGE), incubationTime(5.0f), elapsedTime(0.0f), 
    plant(new Plant(DEFAULT_PLANT, x, y)) {}

void Seed::Draw() const {
    DrawCircle(rec.x, rec.y, 30, color);  
}

void Seed::Update(float deltaTime) {
    if (elapsedTime < incubationTime) {
        elapsedTime += deltaTime; 
    } 
}
