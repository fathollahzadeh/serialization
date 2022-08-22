#include "Client.h"

Client::~Client() {
    if (isValid())
        close(mSocket);
}

Client::Client(string ip, int port) {
    if (!Socket::create()) {
        throw SocketException("Could not create client socket.");
    }

    if (!Socket::connect(ip, port)) {
        throw SocketException("Could not bind to port.");
    }
}
