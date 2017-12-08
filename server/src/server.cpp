#include <iostream>
#include <vector>
#include <random>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#include "../headers/server.h"
#include "../headers/object.h"
#include "../headers/ball.h"

std::vector<Object *> *Server::getObjects() { return this->objects; }
void Server::setObjects(Object *object) { this->objects->push_back(object); }

void Server::move()
{
    for (auto &i : *this->getObjects()) {
        i->move();
        double x = 0,
               y = 0;
        x = i->getX();
        y = i->getY();
        write(onesockfd, &x, sizeof(x));
        write(onesockfd, &y, sizeof(y));
    }
}

void Server::start()
{
    while (1)
        move();
}

Server::Server()
{
    std::cout << "Initialization server" << std::endl;

    this->objects = new std::vector<Object *>;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Ball *ball = new Ball();
    ball->setVecX(dist(mt));
    ball->setVecY(dist(mt));

    setObjects(ball);

    int port = 1337;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    std::cout << "Initializaion done" << std::endl;

    std::cout << "Wait for client..." << std::endl;
    listen(sockfd, 5);
    socklen_t addrlen = 0;
    onesockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &addrlen);
    std::cout << "Client connected: " << inet_ntoa(cli_addr.sin_addr) << std::endl;
}
