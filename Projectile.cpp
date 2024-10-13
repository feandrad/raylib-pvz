#include "Projectile.h"

void Projectile::Update(float deltaTime) {
    position.x += speed * deltaTime; 
    if (position.x > GetScreenWidth()) {
        isActive = false; // Mark inactive if it goes off-screen
    }
}

void Projectile::Draw() const {
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 5.0f, MAROON);
}

void Projectile::OnCollision(Entity* other) {
    if (Zombie* zombie = dynamic_cast<Zombie*>(other)) {
        if (CheckCollisionPointRec(position, zombie->GetCollisionBoundary())) {
            zombie->TakeDamage(10); 
            isActive = false; 
        }
    }
}