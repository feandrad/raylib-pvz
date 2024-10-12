#pragma once

#include "raylib.h"
#include "Placeable.h"
#include <vector>

class Plant : public Placeable {

private:
    int health;
public:
    Rectangle rec;
    Color color;
    int fireRate;
    float lastShotTime;

    Plant();  
    Plant(float x, float y); 

    bool GetHealth() { return health; }

    bool CanShoot(float currentTime);  // Check if the plant can shoot
    void Shoot(std::vector<Rectangle>& projectiles, float currentTime); 
};
