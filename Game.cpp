#include "Game.h"
#include "Random.h"

Game::Game(Font font) : gui(Gui(font)) {
    laneYPositions.resize(gridRows);
    int startY = (GetScreenHeight() - totalHeight) / 2; 

    for (int i = 0; i < gridRows; i++) {
        laneYPositions[i] = startY + (i * cellSize) + (cellSize / 2);

        for (int j = 0; j < gridCols; j++) {
            board[i][j] = nullptr; 
        }
    }
}

void Game::GameLoop() {
    float deltaTime = GetFrameTime();
    Update(deltaTime);
    CheckProjectileCollisions();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    Draw();
    EndDrawing();
}

void Game::HandleMouseInput() {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && seedCount > 0) {
        Vector2 mousePos = GetMousePosition();
        
        int startY = (GetScreenHeight() - totalHeight) / 2;
        int gridX = (mousePos.x - leftColumnWidth) / cellSize;
        int gridY = (mousePos.y - startY) / cellSize;

        if (gridY >= 0 && gridY < gridRows && gridX >= 0 && gridX < gridCols &&
            board[gridY][gridX] == nullptr) {

            int x = gridX * cellSize + leftColumnWidth + cellSize / 2;
            int y = gridY * cellSize + startY + cellSize / 2;

            std::cout << "Placing seed at (" << gridX << ", " << gridY << ")" << std::endl;

            Seed* seed = entityPool.CreateEntity<Seed>(x, y);

            board[gridY][gridX] = seed;
            entityLaneMap[seed] = gridY; 

            seedCount--;
        }
    }
}

void Game::CheckProjectileCollisions() {
    // Add collision logic here
}


void Game::UpdateBoard(float deltaTime) {
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            if (board[i][j] != nullptr) {
                if (Seed* seed = dynamic_cast<Seed*>(board[i][j])) {
                    seed->Update(deltaTime); 
                    if (seed->elapsedTime >= seed->incubationTime) {
                        board[i][j] = seed->plant; 
                        entityLaneMap.erase(seed);  
                        entityPool.DestroyEntity(seed); 
                    }
                } else if (Plant* plant = dynamic_cast<Plant*>(board[i][j])) {
                    plant->Update(deltaTime);
                    if (plant->CanAttack()) {
                        Projectile* shot = plant->Attack();
                        entityLaneMap[shot] = i;
                    }
                }
            }
        }
    }
}

void Game::UpdateSeed(float deltaTime) {
    seedProgress += seedIncrement * deltaTime;
    if (seedProgress >= seedProgressMax) {
        seedProgress = 0;
        seedCount++;
    }
}

void Game::UpdateEntities(float deltaTime) {
    for (auto& [entity, lane] : entityLaneMap) {
        entity->Update(deltaTime);
    }
}

void Game::SpawnZombies() {
    for (int i = 0; i < waveCount; i++) {
        int lane = Random::Int(gridRows - 1); 
        float x = screenWidth; 
        float y = laneYPositions[lane]; 

        Zombie* zombie = entityPool.CreateEntity<Zombie>(DEFAULT_ZOMBIE, Vector2{x, y});
        entityLaneMap[zombie] = lane;

        std::cout << "Spawned Zombie at (" << x << ", " << y << ") in lane " << lane << std::endl;
    }
}

void Game::UpdateWave(float deltaTime) {
    nextWaveProgress += nextWaveIncrement * deltaTime;
    if (nextWaveProgress >= nextWaveMax) {
        nextWaveProgress = 0;
        waveCount++;
        SpawnZombies();
    }
}

void Game::DrawCheckerboard() {
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

void Game::DrawEntities() {
    for (auto& [entity, lane] : entityLaneMap) {
        entity->Draw();
    }
}

void Game::DrawUi() {
    gui.Draw(seedProgress / seedProgressMax, nextWaveProgress / nextWaveMax);

    DrawText(TextFormat("Seeds: %d", seedCount), 10, 10, 10, MAROON);
    DrawText(TextFormat("Wave: %d", waveCount), 10, 30, 10, MAROON);
}

void Game::Update(float deltaTime) {
    HandleMouseInput();
    UpdateBoard(deltaTime);
    UpdateSeed(deltaTime);
    UpdateWave(deltaTime);
    UpdateEntities(deltaTime);
    gui.Update(deltaTime);
}

void Game::Draw() {
    DrawCheckerboard();
    DrawEntities();
    DrawUi();
}
