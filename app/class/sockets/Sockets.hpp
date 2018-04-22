#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <tuple>

#include "../error/error.hpp"

using namespace std;

class Sockets{
    private:
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
    public:
        ~Sockets();
        Sockets(string ip, int host);
        void close();
        void sendStructPosition(double x, double y, double z);
        void sendNbParticules(int n);
};

#endif
