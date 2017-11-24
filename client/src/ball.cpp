#include <iostream>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#include "../headers/ball.h"


Ball::Ball() 
{
    int port = 1337;

    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
}

void Ball::move()
{
    double x, y;
    read(sockfd, &x, sizeof(x));
    read(sockfd, &y, sizeof(y));
    this->setX(x);
    this->setY(y);
}
