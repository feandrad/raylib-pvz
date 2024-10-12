#pragma once

#include "raylib.h"

static const int leftColumnWidth = 100;

class Gui {
public:
    float seedMaxWidth = leftColumnWidth - 20;
    float seedBarWidth = 0;
    float waveMaxWidth = 500;
    float waveBarWidth = 0;
    float barHeight = 10;
    float fillSpeed = 10;

    Font* font;

    Gui(Font* font) : font(font) {}

    void Draw(float seedRate, float waveRate);
    void Update(float deltaTime);
};
