#include "Sockets.hpp"
#include <omp.h>

Sockets::~Sockets(){}

Sockets::Sockets(string ip, int host){
    portno = atoi(to_string(host).c_str());
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(ip.c_str());
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        Error::error("sockets.cpp", "ERROR connecting");
}

struct position {
    double x;
    double y;
    double z;
} position;

void Sockets::sendStructPosition(double x, double y, double z){
    position.x = x;
    position.y = y;
    position.z = z;
    n = write(sockfd, &position, 24);
    if (n < 0)
        Error::error("sockets.cpp", "ERROR writing to socket");
}

void Sockets::close(){
    n = write(sockfd, NULL, sizeof(position));
    ::close(sockfd);
}

void Sockets::sendNbParticules(int n){
    position.x = n;
    position.y = n;
    position.z = n;
    int res = write(sockfd, &position, 24);
    if (res < 0){
        Error::error("sockets.cpp", "ERROR send number particules");
    }
}
