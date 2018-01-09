#ifndef CLIENT_H
#define CLIENT_H

#include <vector>

#include "../headers/object.h"

#define BALL 2
#define PL1 0
#define PL2 1

class Client 
{
    private:
        std::vector<Object *> *objects;
        int sockfd;
        int id;

    public:
        void setObjects(Object *);
        std::vector<Object *> *getObjects();

        void recv();
        void send();
        void game();
        void start();
        Client();
        ~Client();
};

#endif
