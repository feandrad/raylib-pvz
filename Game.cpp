#include "Game.h"

Game::Game() {
    LoadResources();
    InitGame();
}

Game::~Game() {
    for (Zombie* z : zombies) {
        delete z; 
    }
    delete gui;
}

void Game::GameLoop() {
    float deltaTime = GetFrameTime();
    Update(deltaTime);
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Draw();
    EndDrawing();
}

void Game::LoadResources() {
    font = LoadFont("res/pixelplay.png");
    gui = new Gui(&font);
}

void Game::InitGame() {
    laneYPositions.resize(gridRows);
    int startY = (GetScreenHeight() - totalHeight) / 2; 

    for (int i = 0; i < gridRows; i++) {
        laneYPositions[i] = startY + (i * cellSize) + (cellSize / 2);

        for (int j = 0; j < gridCols; j++) {
            board[i][j] = nullptr; 
        }
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
            board[gridY][gridX] = new Seed(x, y);
            seedCount--;
        }
    }
}

void Game::UpdateBoard(float deltaTime) {
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

void Game::UpdateSeed(float deltaTime) {
    seedProgress += seedIncrement * deltaTime;
    if (seedProgress >= seedProgressMax) {
        seedProgress = 0;
        seedCount++;
    }
}

void Game::UpdateEntities(float deltaTime) {
    for (auto* z : zombies) {
        z->Update(deltaTime);
    }

    for (size_t index = 0; index < projectiles.size(); ) {
        Projectile* p = projectiles[index];
        p->Update(deltaTime); 

        if (!p->isActive) { 
            delete p;
            projectiles.erase(projectiles.begin() + index); 
        } else {
            ++index; 
        }
    }
}


void Game::SpawnZombies() {
    for (int i = 0; i < gridRows; i++) {
        float x = screenWidth; 
        float y = laneYPositions[i];
        zombies.push_back(new Zombie(DEFAULT_ZOMBIE, {x, y}));
        std::cout << "Spawned Zombie at (" << x << ", " << y << ")" << std::endl;
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

void Game::DrawEntities() {
    for (auto* z : zombies) {
        z->Draw();
    }

    for (auto* p : projectiles) {
        p->Draw();
    }
}

void Game::DrawUi() {
    gui->Draw(seedProgress / seedProgressMax, nextWaveProgress / nextWaveMax);

    DrawText(TextFormat("Seeds: %d", seedCount), 10, 10, 10, MAROON);
    DrawText(TextFormat("Wave: %d", waveCount), 10, 30, 10, MAROON);
}

void Game::Draw() {
    DrawCheckerboard();
    DrawEntities();
    DrawUi();
}

void Game::Update(float deltaTime) {
    HandleMouseInput();
    UpdateBoard(deltaTime);
    UpdateSeed(deltaTime);
    UpdateWave(deltaTime);
    UpdateEntities(deltaTime);
    gui->Update(deltaTime);
}
