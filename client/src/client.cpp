#include <iostream>
#include <arpa/inet.h>
#include <SDL2/SDL.h> 
#include <unistd.h>

#include "../headers/client.h"
#include "../headers/ball.h"
#include "../headers/gfx.h"
#include "../headers/pane.h"
#include "../headers/settings.h"

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
    double coords[10] = { 0 };
    read(sockfd, &coords, sizeof(coords));
    for (int i = 0; i < (int) this->objects->size(); i++) {
        this->objects->at(i)->setX(coords[i * 2]);
        this->objects->at(i)->setY(coords[i * 2 + 1]);
    }
}

void Client::game()
{
	SDL_Event e;
    bool quit = false;

	while(!quit) {
		while(SDL_PollEvent( &e ) != 0) {
			if(e.type == SDL_QUIT) 
				quit = true;
            if (e.type == SDL_KEYDOWN) 
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;

            /*
             *if (e.type == SDL_KEYDOWN) 
             *    if (e.key.keysym.sym == SDLK_j)
             */

        }
        this->send();
        this->recv();
        for (auto &i : *this->objects)
            i->move();
        draw(this->objects);
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
}

Client::~Client()
{
    std::cout << "Bye-bye" << std::endl;
    clear();
}
