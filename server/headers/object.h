#ifndef OBJ_H
#define OBJ_H

const static int SCREEN_HEIGHT = 600;
const static int SCREEN_WIDTH = 800; 

class Object
{
    protected:
        double vecX, vecY,
               x, y;
    public:
        virtual void move() = 0;

        void setX(double x);
        double getX();

        void setY(double y);
        double getY();
};

#endif
