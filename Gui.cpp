#include "Gui.h"
#include <iostream>

void Gui::Draw(float seedRate, float waveRate) {
    DrawRectangle(10, 10, seedMaxWidth, barHeight, GRAY);
    DrawRectangle(10, 10, seedMaxWidth * seedRate, barHeight, ORANGE);

    DrawRectangle(100, 10, waveMaxWidth, barHeight, GRAY);
    DrawRectangle(100, 10, waveMaxWidth * waveRate, barHeight, RED);
}

void Gui::Update(float deltaTime) {

}
