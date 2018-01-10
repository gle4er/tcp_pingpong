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
        int masterSD, clientSD[2] = { 0 },
            peerSD[2] = { 0 }; //Socket Descriptor
        fd_set readSD, typeSD;
        void messaging();
        void messageSetup();

    public:
        std::vector<Object *> *getObjects();
        void setObjects(Object *);

        void tick();
        void start();

        Server();
};

#endif
