// PvZ.cpp
#include "PvZ.h"

void InitGame() {
    // Initialize the grid
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            board[i][j] = nullptr; 
        }
    }
}

void DrawCheckerboard() {
    // Calculate the total height of the checkerboard
    int totalHeight = gridRows * cellSize;

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

void DrawGame() {
    DrawCheckerboard();
    gui->Draw();
}

void GameLoop() {
    float deltaTime = GetFrameTime();

    UpdateBoard(deltaTime);
    gui->Update(deltaTime);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawGame();
    EndDrawing();
}

int main() {
    InitWindow(screenWidth, screenHeight, "Plants vs Zombies-like Game - Checkerboard Field and Seed Bar");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        GameLoop();
    }

    CloseWindow();
    return 0;
}
