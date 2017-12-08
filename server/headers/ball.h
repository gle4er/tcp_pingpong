#ifndef BALL_H
#define BALL_H

#include "../headers/object.h"

const static int SCREEN_HEIGHT = 600;
const static int SCREEN_WIDTH = 800; 

class Ball : public Object
{
    private:
        double vecX, vecY;

    public:
        Ball();

        void setVecX(double vecX);
        double getVecX();

        void setVecY(double vecX);
        double getVecY();

        void move();
};

#endif
