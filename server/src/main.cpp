#include <iostream>

#include "../headers/server.h"

#define MAX_CLIENT 2

int main()
{
    Server *serv = new Server();
    serv->start();
    return 0;
}
