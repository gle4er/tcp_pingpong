#include <iostream>
#include <thread>
#include <chrono>

#include "../headers/ball.h"

int main()
{
    Ball *ball = new Ball();
    while (1) {
        ball->move();
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
