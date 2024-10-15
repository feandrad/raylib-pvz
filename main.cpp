#include "Game.h"

int main() {
    InitWindow(screenWidth, screenHeight, "Plants vs Zombies-like Game - Checkerboard Field and Seed Bar");
    SetTargetFPS(60);

    Font font = LoadFont("res/pixelplay.png");
    Game game = Game(font);

    while (!WindowShouldClose()) {
        game.GameLoop();
    }

    CloseWindow();
    return 0;
}
