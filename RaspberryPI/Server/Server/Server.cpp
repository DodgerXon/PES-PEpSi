#include "Server.h"
#include <unistd.h>
#include <sys/resource.h>

Server::Server() {
    // Create the socket
    if ((listenSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Can't create socket: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    addressLength = sizeof(address);

    int opt = 1;
    if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "setsockopt error: " << errno << std::endl;
        close(listenSock);
        exit(EXIT_FAILURE);
    }
}

bool Server::Bind(int port) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(listenSock, (struct sockaddr*)&address, addressLength) < 0) {
        std::cerr << "Socket bind error: " << errno << std::endl;
        return false;
    }
    return true;
}

bool Server::Listen() {
    if (listen(listenSock, 3) < 0) {
        std::cerr << "Socket listen error: " << errno << std::endl;
        return false;
    }
    return true;
}

bool Server::Accept() {
    sock = accept(listenSock, (struct sockaddr*)&address, &addressLength);
    if (sock < 0) {
        std::cerr << "Socket accept error: " << errno << std::endl;
        return false;
    }
    return true;
}

void Server::CloseClient() {
    if (sock >= 0) {
        close(sock);
        sock = -1;
    }
}
