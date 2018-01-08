#include <iostream>
#include <vector>

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
#include "../headers/pane.h"

std::vector<Object *> *Server::getObjects() { return this->objects; }
void Server::setObjects(Object *object) { this->objects->push_back(object); }

void Server::move()
{
    for (auto &i : *this->getObjects()) 
        i->move();

    double sendData[10] = { 0 };
    for (int i = 0; i < (int) this->objects->size(); i++) {
        sendData[i * 2] = this->objects->at(i)->getX();
        sendData[i * 2 + 1] = this->objects->at(i)->getY();
    }
    Ball *ball = (Ball *) this->objects->at(2);
    sendData[8] = ball->getScore(0);
    sendData[9] = ball->getScore(1);
    write(onesockfd, &sendData, sizeof(sendData));
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

    Pane *pl1 = new Pane();
    setObjects(pl1);
    Pane *pl2 = new Pane();
    setObjects(pl2);

    Ball *ball = new Ball(pl1, pl2);
    setObjects(ball);

    int port = 1337;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    int clientNum = 0;
    std::cout << "Initializaion done" << std::endl;

    std::cout << "Wait for clients..." << std::endl;
    listen(sockfd, 5);
    socklen_t addrlen = 0;
    onesockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &addrlen);
    std::cout << "Client " << clientNum  << "connected" << std::endl;
    write(onesockfd, &clientNum, sizeof(clientNum));
}
