#pragma once

#include "raylib.h"
#include "Gui.h"
#include "Placeable.h"
#include "Plant.h"
#include "Seed.h"
#include "Zombie.h"
#include <vector>

// Game Constants
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
float nextWave = 10.0f;
const float nextWaveIncrement = nextWaveMax / nextWave;

// Game Variables
std::vector<Zombie> zombies;
std::vector<Rectangle> projectiles;
std::vector<Placeable> plants;
int seedCount = 0;
float seedProgress = 0;
int waveCount = 0;
float nextWaveProgress = 0;

Placeable* board[gridRows][gridCols];
Gui* gui;

// Function Declarations
void InitGame();
void GameLoop();
void DrawCheckerboard();
void DrawGame();
