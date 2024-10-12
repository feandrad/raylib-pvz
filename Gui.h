#pragma once

#include "raylib.h"

static const int leftColumnWidth = 100;

class Gui {
public:
    float barMaxWidth = leftColumnWidth - 20;
    float barWidth = 0;
    float barHeight = 10;
    float fillSpeed = 10;

    Font* font;

    Gui(Font* font) : font(font) {}

    void Draw(float percent);
    void Update(float deltaTime);
};
