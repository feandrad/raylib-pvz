#include "Plant.h"

Plant::Plant() {
    this->rec = {0, 0, float(70), float(70)};
    this->color = GREEN;
    this->health = 100;
    this->fireRate = 2;
    this->lastShotTime = -fireRate;
}

Plant::Plant(float x, float y) {
    this->rec = {x, y, float(70), float(70)};
    this->color = GREEN;
    this->health = 100;
    this->fireRate = 2;
    this->lastShotTime = -fireRate;
}

bool Plant::CanShoot(float currentTime) {
    return currentTime - lastShotTime > fireRate;
}

void Plant::Shoot(std::vector<Rectangle>& projectiles, float currentTime) {
    projectiles.push_back({rec.x + rec.width, rec.y + rec.height / 2 - 5, 10, 10});
    lastShotTime = currentTime;
}
