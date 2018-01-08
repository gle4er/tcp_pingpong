#ifndef PANE_H
#define PANE_H

#include "../headers/object.h"

class Pane : public Object
{
    private:
        double sizeY,
               sizeX;

    public:
        Pane();
        void move();
        double getSizeX();
        double getSizeY();
};

#endif
