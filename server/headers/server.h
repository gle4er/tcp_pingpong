#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "../headers/object.h"

class Server
{
    private:
        std::vector<Object *> *objects;
        int sockfd, onesockfd;
    public:
        std::vector<Object *> *getObjects();
        void setObjects(Object *);

        void move();
        void start();

        Server();
};

#endif
