#ifndef BALL_H
#define BALL_H

#include "../headers/object.h"

const static int SCREEN_HEIGHT = 800;
const static int SCREEN_WIDTH = 600; 

class Ball : public Object
{
    public:
        Ball();

        void setVecX(double vecX);
        double getVecX();

        void setVecY(double vecX);
        double getVecY();

        void move();
        
    private:
        double vecX, vecY;
        int sockfd;
        int onesockfd;
};

#endif
