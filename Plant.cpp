#include "Plant.h"
#include <iostream>

bool Plant::CanAttack() const {
    return attackCooldown > stats.fireRate;
}

Projectile* Plant::Attack() {
    attackCooldown = 0.0f;

    float adjustedX = position.x - stats.width / 2; 
    float adjustedY = position.y - stats.height / 2; 
    return new Projectile(DEFAULT_PROJECTILE, {position.x, position.y});
}

Rectangle Plant::GetCollisionBoundary() const {
    float adjustedX = position.x - stats.width / 2; 
    float adjustedY = position.y - stats.height / 2; 
    return Rectangle{ adjustedX, adjustedY, stats.width, stats.height }; 
}

void Plant::Update(float deltaTime) {
    attackCooldown += deltaTime;
    // std::cout << "Cooldown ( " << attackCooldown << " / " << stats.fireRate << " )" << std::endl;
}

void Plant::Draw() const {
    DrawRectangleRec(GetCollisionBoundary(), color); 
}
