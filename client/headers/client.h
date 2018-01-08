#ifndef CLIENT_H
#define CLIENT_H

#include <vector>

#include "../headers/object.h"

class Client 
{
    protected:
        std::vector<Object *> *objects;
        int sockfd;
        int id;

    public:
        void setObjects(Object *);
        std::vector<Object *> *getObjects();

        void recv();
        void game();
        void start();
        Client();
        ~Client();
};

#endif
