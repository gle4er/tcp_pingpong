#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <sys/socket.h>

#include "../headers/object.h"

#define BALL 2
#define PL1 0
#define PL2 1

class Server
{
    private:
        std::vector<Object *> *objects;
        int masterSD, clientSD[2] = { 0 }, maxSD; //Socket Descriptor
        fd_set readSD;

    public:
        std::vector<Object *> *getObjects();
        void setObjects(Object *);

        void move();
        void start();

        Server();
};

#endif
