#include "Projectile.h"

void Projectile::Update(float deltaTime) {
    position.x += stats.speed * deltaTime; 
    if (position.x > GetScreenWidth()) {
        isActive = false; // Mark inactive if it goes off-screen
    }
}

void Projectile::Draw() const {
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 5.0f, MAROON);
}

void Projectile::OnCollision(Zombie* zombie) {
    zombie->TakeDamage(stats.dmg); 
    isActive = false; 
}