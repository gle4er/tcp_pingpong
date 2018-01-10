#include <iostream>
#include <vector>
#include <thread>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../headers/server.h"
#include "../headers/object.h"
#include "../headers/ball.h"
#include "../headers/pane.h"

std::vector<Object *> *Server::getObjects() { return this->objects; }
void Server::setObjects(Object *object) { this->objects->push_back(object); }

void Server::tick()
{
    double recvData[3] = { 0 };
    
    for (int i = 0; i < 2; i++) {
        int sd = clientSD[i];

        read(sd, &recvData, sizeof(recvData));
        int id = recvData[2];
        objects->at(id)->setX(recvData[0]);
        objects->at(id)->setY(recvData[1]);

    }

    objects->at(BALL)->move();

    double sendData[10] = { 0 };

    for (int i = 0; i < (int) this->objects->size(); i++) {
        sendData[i * 2] = this->objects->at(i)->getX();
        sendData[i * 2 + 1] = this->objects->at(i)->getY();
    }
    Ball *ball = (Ball *) this->objects->at(2);
    sendData[8] = ball->getScore(0);
    sendData[9] = ball->getScore(1);

    for (int i = 0; i < 2; i++) {
        int sd = clientSD[i];

        write(sd, &sendData, sizeof(sendData));
    }
}

void Server::messaging()
{
    std::cout << "Enabling and setup messaging" << std::endl;

    int rc = 0;
    int msgSD = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    int port = 1338;
    serv_addr.sin_port = htons(port);

    int opt = 1;
    rc = setsockopt(msgSD, SOL_SOCKET, SO_REUSEADDR, (int *) &opt, sizeof(int));
    if (rc < 0)
        perror("setsockopt");
    rc = bind(msgSD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (rc < 0)
        perror("bind");

    rc = listen(msgSD, 3);
    if (rc < 0)
        perror("listen");

    socklen_t addrlen = 0;

    struct pollfd fds[2];

    for (int i = 0; i < 2; i++) {
        peerSD[i] = accept(msgSD, (struct sockaddr *) &cli_addr, &addrlen);
        if (peerSD[i] <= 0)
            perror("accept");
        fds[i].fd = peerSD[i];
        fds[i].events = POLLIN;
        int tmp = 0;
        write(peerSD[i], &tmp, sizeof(int));
    }

    std::cout << "Done" << std::endl;

    char *msg = (char *) malloc(sizeof(*msg) * 100);
    while (1) {
        int rc = poll(fds, 2, -1);
        if (rc < 0)
            perror("poll");
        for (int i = 0; i < 2; i++) {
            int sd = peerSD[i];
            if (fds[i].revents & POLLIN) {
                read(sd, msg, sizeof(char) * 100);
                int indx = i ^ 1;
                sd = peerSD[indx];
                std::cout << i << " -> " << indx << " : " << msg << std::endl;
                write(sd, msg, sizeof(char) * 100);
            }
        }
    }
    free(msg);
}

void Server::start()
{
    while (1)
        tick();
}

Server::Server()
{
    std::cout << "Initialization server" << std::endl;

    std::thread msgThread(&Server::messaging, this);
    msgThread.detach();

    this->objects = new std::vector<Object *>;

    Pane *pl1 = new Pane();
    setObjects(pl1);
    Pane *pl2 = new Pane();
    setObjects(pl2);

    Ball *ball = new Ball(pl1, pl2);
    setObjects(ball);

    int port = 1337;

    this->masterSD = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, cli_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    int opt = 1;
    setsockopt(masterSD, SOL_SOCKET, SO_REUSEADDR, (int *) &opt, sizeof(int));

    bind(masterSD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    std::cout << "Initializaion done" << std::endl;

    std::cout << "Wait for clients..." << std::endl;
    int clientNum = 0;
    listen(masterSD, 3);
    socklen_t addrlen = 0;
    for (int i = 0; i < 2; i++) {
        clientSD[i] = accept(masterSD, (struct sockaddr *) &cli_addr, &addrlen);
        std::cout << "Client " << clientNum << " connected" << std::endl;
        write(clientSD[i], &clientNum, sizeof(clientNum));
        clientNum++;
    }

    for (int i = 0; i < 2; i++) {
        int flg = 1;
        write(clientSD[i], &flg, sizeof(flg));
    }
}
