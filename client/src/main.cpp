#include <iostream>

#include "../headers/client.h"

int main()
{
    Client *client = new Client();
    client->start();
    return 0;
}
