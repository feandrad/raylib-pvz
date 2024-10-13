#include "Plant.h"

Plant::Plant(PlantStats pStats, float x, float y)
    : stats(pStats), lastShotTime(0.0f), color(GREEN) {
    this->position = {x, y};
}

bool Plant::CanShoot(float currentTime) const {
    return currentTime - lastShotTime > stats.fireRate;
}

void Plant::Shoot(float currentTime) {
    lastShotTime = currentTime;
}

Rectangle Plant::GetCollisionBoundary() const {
    float adjustedX = position.x - stats.width / 2; 
    float adjustedY = position.y - stats.height / 2; 
    return Rectangle{ adjustedX, adjustedY, stats.width, stats.height }; 
}

void Plant::Update(float deltaTime) {}

void Plant::Draw() const {
    DrawRectangleRec(GetCollisionBoundary(), color); 
}
