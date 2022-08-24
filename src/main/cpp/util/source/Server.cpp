#include "Server.h"


Server::Server(int port) {
    if (!Socket::create()) {
        throw SocketException("Could not create server socket.");
    }

    if (!Socket::bind(port)) {
        throw SocketException("Could not bind to port.");
    }

    if (!Socket::listen()) {
        throw SocketException("Could not listen to socket.");
    }
}

Server::~Server() {}