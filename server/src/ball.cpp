#include <iostream>
#include <random>

#include "../headers/ball.h"
#include "../headers/pane.h"

Ball::Ball() 
{
    //setX(SCREEN_WIDTH / 2);
    //setY(SCREEN_HEIGHT / 2);
}

void Ball::genVec()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-8.0, 8.0);
    do {
        this->setVecX(dist(mt));
        this->setVecY(dist(mt));
        //this->setVecY(0);
    } while (std::abs(this->getVecX()) < 4);
}

Ball::Ball(Pane *pl1, Pane *pl2)
{
    this->setX(SCREEN_WIDTH / 2);
    this->setY(SCREEN_HEIGHT / 2);

    this->genVec();

    this->R = 5;
    this->pl1 = pl1;
    this->pl2 = pl2;
    this->score = new int(2);
    this->score[0] = 0;
    this->score[1] = 0;
}

int checkHeight(double y, Pane *pl)
{
    double y1 = pl->getY() - pl->getSizeY();
    double y2 = pl->getY() + pl->getSizeY();
    return y1 <= y && y <= y2;
}

int Ball::checkCollision()
{
    double x = this->getX() + this->getVecX(),
           y = this->getY() + this->getVecY(),
           xPl1 = pl1->getX() + pl1->getSizeX() + this->R * 2,
           xPl2 = pl2->getX() - pl2->getSizeX() - this->R * 2;

    if (x <= xPl1) {
        if (checkHeight(y, this->pl1)) 
            return 1;
    }
    else if (x >= xPl2) {
        if (checkHeight(y, this->pl2)) 
            return 1;
    }

    return 0;
}

void Ball::resetBall()
{
    this->setX(SCREEN_WIDTH / 2);
    this->setY(SCREEN_HEIGHT / 2);
    this->genVec();
}

void Ball::move()
{
    double x, y;

    x = this->getX() + getVecX();
    y = this->getY() + getVecY();

    if (x > SCREEN_WIDTH) {
        int score = getScore(0);
        score++;
        setScore(0, score);
        resetBall();
        return;
    }
    else if (x < 0) {
        int score = getScore(1);
        score++;
        setScore(1, score);
        resetBall();
        return;
    }

    else if (checkCollision())
        setVecX(getVecX() * -1);

    else if (y > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT;
        this->setVecY(this->getVecY() * -1);
    }
    else if (y < 0) {
        y = 0;
        this->setVecY(this->getVecY() * -1);
    }
    
    this->setX(x);
    this->setY(y);
}

void Ball::setVecX(double vecX) { this->vecX = vecX; }
double Ball::getVecX() { return vecX; }

void Ball::setVecY(double vecY) { this->vecY = vecY; }
double Ball::getVecY() { return vecY; }

void Ball::setScore(int ind, int score) { this->score[ind] = score; }
void Ball::setScore(int *score)
{
    this->score[0] = score[0];
    this->score[1] = score[1];
}

int *Ball::getScore() { return this->score; }
int Ball::getScore(int ind) { return this->score[ind]; }
