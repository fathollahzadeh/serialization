#include "Client.h"

Client::~Client() {
    if (isValid())
        close(mSocket);
}

Client::Client(const string& ip, int port) {
    if (!Socket::create()) {
        throw std::runtime_error("Could not create client socket.");
    }

    if (!Socket::connect(ip, port)) {
        throw std::runtime_error("Could not bind to port.");
    }
}
