#include "PvZ.h"
#include <iostream>
#include <vector>

void LoadResources() {
    font = LoadFont("res/pixelplay.png");
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

void HandleMouseInput() {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && seedCount > 0) {
        Vector2 mousePos = GetMousePosition();
        
        int startY = (GetScreenHeight() - totalHeight) / 2;
        int gridX = (mousePos.x - leftColumnWidth) / cellSize;
        int gridY = (mousePos.y - startY) / cellSize;

        if (board[gridY][gridX] == nullptr &&
            gridX >= 0 && gridX < gridCols && 
            gridY >= 0 && gridY < gridRows) {

            int x = gridX * cellSize + leftColumnWidth;
            int y = gridY * cellSize + startY;

            std::cout << "Placing seed at (" << gridX << ", " << gridY << ")" << std::endl;
            board[gridY][gridX] = new Seed(x, y);

            seedCount--;
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

                } else if (Plant* plant = dynamic_cast<Plant*>(board[i][j])) {
                    plant->Update(deltaTime);
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

void UpdateEntities(float deltaTime) {
    for (Zombie* z : zombies) {
        z->Update(deltaTime);
    }

    for (Entity* p : projectiles) {
        p->Update(deltaTime);
    }
}

void SpawnZombies() {
    for (int i = 0; i < gridRows; i++) {
        float x = screenWidth; // Start at the far right of the screen
        float y = (GetScreenHeight() - totalHeight) / 2 + i * cellSize; // Position according to lane
        zombies.push_back(new Zombie(x, y, 50.0f, 100));
        std::cout << "Spawned Zombie at (" << x << ", " << y << ")" << std::endl;
    }
}

void UpdateWave(float deltaTime) {
    nextWaveProgress += nextWaveIncrement * deltaTime;
    if (nextWaveProgress >= nextWaveMax) {
        nextWaveProgress = 0;
        waveCount++;
        SpawnZombies();
    }
}

void DrawEntities() {
    for (Zombie* z : zombies) {
        z->Draw();
    }

    for (Entity* p : projectiles) {
        p->Draw();
    }
}

void DrawUi() {
    gui->Draw(seedProgress / seedProgressMax, nextWaveProgress / nextWaveMax);

    DrawText(TextFormat("Seeds: %d", seedCount), 10, 10, 10, MAROON);
    // DrawText(TextFormat("Seed Progress: %f", seedProgress), 10, 20, 10, MAROON);
    
    DrawText(TextFormat("Wave: %d", waveCount), 10, 30, 10, MAROON);
    // DrawText(TextFormat("Wave Progress: %f", nextWaveProgress), 10, 40, 10, MAROON);

}

void DrawGame() {
    DrawCheckerboard();
    DrawEntities();
    DrawUi();
}

void GameLoop() {
    float deltaTime = GetFrameTime();

    HandleMouseInput();

    UpdateBoard(deltaTime);
    UpdateSeed(deltaTime);
    UpdateWave(deltaTime);
    UpdateEntities(deltaTime);
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
