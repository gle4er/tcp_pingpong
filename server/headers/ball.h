#ifndef BALL_H
#define BALL_H

#include "../headers/object.h"
#include "../headers/pane.h"

class Ball : public Object
{
    private:
        Pane *pl1, *pl2;
        int *score;
        double R;

        void genVec();
        void resetBall();
        int checkCollision();

    public:
        Ball();
        Ball(Pane *pl1, Pane *pl2);

        void setVecX(double vecX);
        double getVecX();

        void setVecY(double vecX);
        double getVecY();

        void setScore(int ind, int score);
        void setScore(int *score);
        int *getScore();
        int getScore(int ind);

        void move();
};

#endif
