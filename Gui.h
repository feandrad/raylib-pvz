#pragma once

#include "raylib.h"

static const int leftColumnWidth = 100;


class Gui {
public:
    float barMaxWidth = leftColumnWidth - 20;
    float barWidth = 0;
    float barHeight = 10;
    float fillSpeed = 10;

    void Draw();
    void Update (float deltaTime);
};
