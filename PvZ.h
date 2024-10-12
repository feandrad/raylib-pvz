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

// Game Variables
std::vector<Zombie> zombies;
std::vector<Rectangle> projectiles;

Placeable* board[gridRows][gridCols];
Gui* gui = new Gui();

// Function Declarations
void InitGame();
void GameLoop();
void DrawCheckerboard();
void DrawGame();
