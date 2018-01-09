#ifndef OBJ_H
#define OBJ_H

class Object
{
    private:
        double vecX, vecY,
               x, y;
    public:
        virtual void move() = 0;

        void setX(double x);
        double getX();

        void setY(double y);
        double getY();

        void setVecX(double vecX);
        double getVecX();

        void setVecY(double vecY);
        double getVecY();
};

#endif
