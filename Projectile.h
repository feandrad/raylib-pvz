#include "raylib.h"
#include "Entity.h"
#include "Zombie.h"

class Projectile : public Entity {
public:
    float speed;      
    bool isActive;    

    Projectile(float x, float y, float speed)
        : speed(speed), isActive(true) {
        position = { x, y }; 
    }

    CollisionType GetCollisionType() override {
        return CollisionType::Point; 
    }

    void Update(float deltaTime);
    void Draw() const override;
    void OnCollision(Entity* other);
};
