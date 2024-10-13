#include "Zombie.h"

Zombie::Zombie() {
    this->rec = {0, 0, float(70), float(70)};
    this->color = RED;
    this->speed = 50;
    this->health = 100;
}

Zombie::Zombie(float x, float y, float speed, int health) {
    this->rec = {x, y, float(70), float(70)};
    this->color = RED;
    this->speed = speed;
    this->health = health;
}

bool Zombie::IsDead() {
    return health <= 0;
}

void Zombie::Draw() const {
    float centerX = rec.x + rec.width / 2;
    float centerY = rec.y + rec.height / 2;

    DrawCircle(centerX, centerY, 30, color);  
}

void Zombie::Update(float deltaTime) {
    rec.x -= speed * deltaTime;  
}
