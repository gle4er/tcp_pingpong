#include <iostream>

#include "../headers/pane.h"
#include "../headers/settings.h"

Pane::Pane() 
{
    static int player = 0;
    this->setX(SCREEN_WIDTH * (player % 2));
    this->setY(SCREEN_HEIGHT / 2);

    this->sizeX = SIZE_PANE_X;
    this->sizeY = SIZE_PANE_Y;

    player++;
}

void Pane::move() {}
