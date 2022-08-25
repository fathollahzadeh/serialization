#include "Server.h"


Server::Server(int port, int count) {
    if (!Socket::create()) {
        throw std::runtime_error("Could not create server socket.");
    }

    if (!Socket::bind(port)) {
        throw std::runtime_error("Could not bind to port.");
    }

    if (!Socket::listen(count)) {
        throw std::runtime_error("Could not listen to socket.");
    }
}

Server::~Server() = default;
