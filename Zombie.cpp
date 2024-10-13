#include "Zombie.h"

Zombie::Zombie(ZombieStats z, Vector2 position) : stats(z), color(RED) {
    this->position = position; 
}

bool Zombie::IsDead() const {
    return stats.health <= 0;
}

void Zombie::Draw() const {
    DrawRectangleRec(GetCollisionBoundary(), color); 
}

void Zombie::Update(float deltaTime) {
    position.x -= stats.speed * deltaTime; 
}

Rectangle Zombie::GetCollisionBoundary() const {
    float adjustedY = position.y - stats.height / 2; 
    return Rectangle{ position.x, adjustedY, stats.width, stats.height }; 
}

void Zombie::TakeDamage(int dmg) {
    stats.health -= dmg; 
}
