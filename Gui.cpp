#include "Gui.h"

void Gui::Draw() {
    DrawRectangle(10, 10, barMaxWidth, barHeight, GRAY);
    DrawRectangle(10, 10, barWidth, barHeight, ORANGE);
}

void Gui::Update(float deltaTime) {
  if (barWidth < barMaxWidth) {
        barWidth += fillSpeed * deltaTime;
        if (barWidth > barMaxWidth) barWidth == barMaxWidth;
    } 
}
