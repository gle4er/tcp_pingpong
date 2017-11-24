#include <iostream>
#include <random>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#include "../headers/ball.h"

Ball::Ball() 
{
    setX(SCREEN_WIDTH / 2);
    setY(SCREEN_HEIGHT / 2);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    setVecX(dist(mt));
    setVecY(dist(mt));


    int port = 1337;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(sockfd, 5);
    socklen_t addrlen = 0;
    onesockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &addrlen);
}

void Ball::move()
{
    double x, y;

    x = this->getX();
    y = this->getY();

    if (x + getVecX() > SCREEN_WIDTH ||
        x + getVecX() < 0)
        this->setVecX(this->getVecX() * -1);

    if (y + getVecY() > SCREEN_HEIGHT ||
        y + getVecY() < 0)
        this->setVecY(this->getVecY() * -1);

    write(onesockfd, &x, sizeof(x));
    write(onesockfd, &y, sizeof(y));

    this->setX(getVecX() + x);
    this->setY(getVecY() + y);
}

void Ball::setVecX(double vecX) { this->vecX = vecX; }
double Ball::getVecX() { return vecX; }

void Ball::setVecY(double vecY) { this->vecY = vecY; }
double Ball::getVecY() { return vecY; }
