#include "PvZ.h"
#include <iostream>

void LoadResources() {
    // std::cout << "Open Font..." << std::endl;
    // std::cin.get(); // Wait for user input

    Font font = LoadFont("res/pixantiqua.png");
    gui = new Gui(&font);
}

void InitGame() {
    // Initialize the grid
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            board[i][j] = nullptr; 
        }
    }
}

void DrawCheckerboard() {
    // Calculate the starting Y position to center the checkerboard
    int startY = (GetScreenHeight() - totalHeight) / 2;

    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            Color color = (i + j) % 2 == 0 ? LIGHTGRAY : RAYWHITE; 
            DrawRectangle(j * cellSize + leftColumnWidth, startY + i * cellSize, cellSize, cellSize, color); 

            if (board[i][j] != nullptr) {
                board[i][j]->Draw(); 
            }
        }
    }
}

void UpdateBoard(float deltaTime) {
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            if (board[i][j] != nullptr) {
                if (Seed* seed = dynamic_cast<Seed*>(board[i][j])) {
                    seed->Update(deltaTime); 
                    if (seed->elapsedTime >= seed->incubationTime) {
                        board[i][j] = seed->plant; 
                        delete seed; 
                    }
                }
            }
        }
    }
}

void UpdateSeed(float deltaTime) {
    seedProgress += seedIncrement * deltaTime;
    if (seedProgress >= seedProgressMax) {
        seedProgress = 0;
        seedCount++;
    }
}

void UpdateWave(float deltaTime) {
    nextWaveProgress += nextWaveIncrement * deltaTime;
    if (nextWaveProgress >= nextWaveMax) {
        nextWaveProgress = 0;
        waveCount++;
    }
}

void DrawGame() {
    DrawCheckerboard();
    gui->Draw(seedProgress / seedProgressMax, nextWaveProgress / nextWaveMax);
    DrawText(TextFormat("Seeds: %d", seedCount), 10, 10, 10, MAROON);
    DrawText(TextFormat("Seed Progress: %f", seedProgress), 10, 20, 10, MAROON);

    DrawText(TextFormat("Wave: %d", waveCount), 10, 30, 10, MAROON);
    DrawText(TextFormat("Wave Progress: %f", nextWaveProgress), 10, 40, 10, MAROON);
}

void GameLoop() {
    float deltaTime = GetFrameTime();

    UpdateBoard(deltaTime);
    UpdateSeed(deltaTime);
    UpdateWave(deltaTime);
    gui->Update(deltaTime);

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawGame();
    
    EndDrawing();
}

int main() {
    InitWindow(screenWidth, screenHeight, "Plants vs Zombies-like Game - Checkerboard Field and Seed Bar");
    SetTargetFPS(60);

    LoadResources();

    InitGame();

    while (!WindowShouldClose()) {
        GameLoop();
    }

    CloseWindow();
    return 0;
}
