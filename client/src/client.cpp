#include <iostream>
#include <arpa/inet.h>
#include <SDL2/SDL.h> 
#include <unistd.h>
#include <thread>
#include <sys/poll.h>

#include "../headers/client.h"
#include "../headers/ball.h"
#include "../headers/gfx.h"
#include "../headers/pane.h"
#include "../headers/settings.h"

bool msgFlg = false;

std::vector<Object *> *Client::getObjects() { return this->objects; }
void Client::setObjects(Object *object) { this->objects->push_back(object); }

void Client::send()
{
    int indx = this->id;
    double sendData[3] = { 0 };
    sendData[0] = this->objects->at(indx)->getX();
    sendData[1] = this->objects->at(indx)->getY();
    sendData[2] = indx;
    write(sockfd, &sendData, sizeof(sendData));
}

void Client::recv()
{
    double recvData[10] = { 0 };
    read(sockfd, &recvData, sizeof(recvData));
    for (int i = 0; i < (int) this->objects->size(); i++) {
        this->objects->at(i)->setX(recvData[i * 2]);
        this->objects->at(i)->setY(recvData[i * 2 + 1]);
    }
    this->score[0] = recvData[8];
    this->score[1] = recvData[9];
}

void Client::game()
{
	SDL_Event e;
    bool quit = false;
    int moveIndicator = 0;

	while(!quit) {
		while(SDL_PollEvent( &e ) != 0) {
			if(e.type == SDL_QUIT) 
				quit = true;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;
                if (e.key.keysym.sym == SDLK_j)
                    moveIndicator = 1;
                if (e.key.keysym.sym == SDLK_k)
                    moveIndicator = -1;
                if (e.key.keysym.sym == SDLK_RETURN)
                    msgFlg = true;
            }

            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_j)
                    moveIndicator = 0;
                else if (e.key.keysym.sym == SDLK_k)
                    moveIndicator = 0;
            }
        }

        if (!msgFlg) {
            this->objects->at(this->id)->setVecY(moveIndicator * MOVE_SPEED);
            this->objects->at(this->id)->move();

            this->send();
            this->recv();
            draw(this->objects, score);
        }
    }
}

void Client::messaging()
{
    std::cout << "Setup messaging" << std::endl;
    int port = 1338;

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    int msgfd = socket(AF_INET, SOCK_STREAM, 0);
    if (msgfd < 0)
        perror("socket");
    int rc = connect(msgfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (rc < 0)
        perror("connect");
    int tmp = -1;
    read(msgfd, &tmp, sizeof(int));
    std::cout << "tmp: " << tmp << std::endl;
    std::cout << "rc: " << rc << std::endl;
    struct pollfd readFd;
    readFd.fd = msgfd;
    readFd.events = POLLIN;
    std::cout << "Connected messaging server" << std::endl;

    while (1) {
        if (msgFlg) {
            msgFlg = false;
            char *msg = enterMsg(this->id);
            if (this->id)
                msg[98] = '1';
            else
                msg[98] = '0';
            write(msgfd, msg, sizeof(char) * 100);
            std::cout << "sent: " << msg << std::endl;
            free(msg);
        } else {
            int rc = poll(&readFd, 1, 500);
            if (rc < 0)
                perror("poll");
            if (readFd.revents & POLLIN) {
                char *msg = (char *) malloc(sizeof(*msg) * 100);
                read(msgfd, msg, sizeof(char) * 100);
                msg[98] = ' ';
                enterMsg(msg);
                std::cout <<  msg << std::endl;
                free(msg);
            }
        }
    }
}

void Client::start()
{
    std::cout << "Starting client" << std::endl;
    initGfx();
    game();
}

Client::Client()
{
    std::cout << "Initialization" << std::endl;
    this->id = 0;
    this->objects = new std::vector<Object *>;

    int port = 1337;

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "Connect to server" << std::endl;
    connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    read(sockfd, &this->id, sizeof(this->id));
    std::cout << "Connect successfull: id " << id << std::endl;

    Pane *pl1 = new Pane();
    Pane *pl2 = new Pane();
    Ball *ball = new Ball();
    setObjects(pl1);
    setObjects(pl2);
    setObjects(ball);

    std::cout << "Waiting for second player" << std::endl;
    int readyFlg = 0;
    read(sockfd, &readyFlg, sizeof(readyFlg));

    std::thread msgThread(&Client::messaging, this);
    msgThread.detach();
}

Client::~Client()
{
    std::cout << "Bye-bye" << std::endl;
    clear();
}
