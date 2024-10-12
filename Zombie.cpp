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

void Zombie::Update(float deltaTime) {
    rec.x -= speed * deltaTime;  
}

bool Zombie::IsDead() {
    return health <= 0;
}
