#include <iostream>

#include "../headers/pane.h"

Pane::Pane() 
{
    static int player = 0;
    this->setX(SCREEN_WIDTH * (player % 2));
    this->setY(SCREEN_HEIGHT / 2);

    this->sizeX = 10;
    this->sizeY = 30;

    player++;
}

void Pane::move() {}

double Pane::getSizeX() { return sizeX; }
double Pane::getSizeY() { return sizeY; }
