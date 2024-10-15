#pragma once

#include "raylib.h"
#include "Gui.h"
#include "Entity.h"
#include "Projectile.h"
#include "Plant.h"
#include "Seed.h"
#include "Zombie.h"
#include "EntityPool.h"

#include <algorithm>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 450;
const int gridRows = 5;
const int gridCols = 7;
const int cellSize = 80;
const int totalHeight = gridRows * cellSize;

const float seedProgressMax = 100.0f;
const float seedTime = 5.0f;
const float seedIncrement = seedProgressMax / seedTime;

const float nextWaveMax = 100.0f;
const float nextWave = 10.0f;
const float nextWaveIncrement = nextWaveMax / nextWave;

class Game {
public:
    Game(Font font);
    ~Game() = default;
    void GameLoop();

private:
    int seedCount = 1;
    float seedProgress = 0;
    int waveCount = 0;
    float nextWaveProgress = 0;

private:
    void Update(float deltaTime);
    void Draw();
    void DrawCheckerboard();
    void HandleMouseInput();
    void CheckProjectileCollisions();
    void UpdateBoard(float deltaTime);
    void UpdateSeed(float deltaTime);
    void UpdateEntities(float deltaTime);
    void SpawnZombies();
    void UpdateWave(float deltaTime);
    void DrawEntities();
    void DrawUi();

    Gui gui;
    Entity *board[gridRows][gridCols];
    std::vector<float> laneYPositions;
    EntityPool entityPool;
    std::unordered_map<Entity*, int> entityLaneMap;
};
