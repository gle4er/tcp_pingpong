#include <iostream>


#include "../headers/ball.h"

Ball::Ball() 
{
    setX(SCREEN_WIDTH / 2);
    setY(SCREEN_HEIGHT / 2);
}

void Ball::move()
{
    double x, y;

    x = this->getX();
    y = this->getY();

    if (x + getVecX() > SCREEN_WIDTH ||
        x + getVecX() < 0)
        this->setVecX(this->getVecX() * -1);

    if (y + getVecY() > SCREEN_HEIGHT ||
        y + getVecY() < 0)
        this->setVecY(this->getVecY() * -1);
    
    this->setX(getVecX() + x);
    this->setY(getVecY() + y);
}

void Ball::setVecX(double vecX) { this->vecX = vecX; }
double Ball::getVecX() { return vecX; }

void Ball::setVecY(double vecY) { this->vecY = vecY; }
double Ball::getVecY() { return vecY; }
