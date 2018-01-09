#ifndef PANE_H
#define PANE_H

#include "../headers/object.h"

class Pane : public Object
{
    private:
        double sizeX, sizeY;

    public:
        Pane();
        void move();
};

#endif
