#include "Gui.h"
#include <iostream>

void Gui::Draw(float percent)
{
    DrawRectangle(10, 10, barMaxWidth, barHeight, GRAY);
    DrawRectangle(10, 10, barMaxWidth * percent, barHeight, ORANGE);
}

void Gui::Update(float deltaTime)
{
    if (barWidth < barMaxWidth)
    {
        barWidth += fillSpeed * deltaTime;
        if (barWidth > barMaxWidth)
            barWidth == barMaxWidth;
    }
}
