#ifndef BALL_H
#define BALL_H

#include "../headers/object.h"

class Pane : public Object
{
    public:
        Pane();
        Pane(int player);
        void move();
};

#endif
