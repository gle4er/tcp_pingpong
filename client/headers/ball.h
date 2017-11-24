#ifndef BALL_H
#define BALL_H

#include "../headers/object.h"

class Ball : public Object
{
    public:
        Ball();
        void move();
    private:
        int sockfd;
};

#endif
