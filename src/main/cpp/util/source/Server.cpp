#include "Server.h"


Server::Server(int port, int count) {
    if (!Socket::create()) {
        throw std::runtime_error("Could not create server socket.");
    }

    bool flag = false;
    for (int i = 0; i <1000 && !flag ; ++i) {
        flag = Socket::bind(port);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (!flag){
        throw std::runtime_error("Could not bind to port.");
    }

    if (!Socket::listen(count)) {
        throw std::runtime_error("Could not listen to socket.");
    }
}

Server::~Server() = default;
