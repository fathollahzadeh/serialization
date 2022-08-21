#include "Client.h"

Client::Client(const sockaddr_in &mAddr) : sockaddr(mAddr) {}

Client::~Client() {}

const sockaddr_in &Client::getMAddr() const {
    return mAddr;
}

Client::Client(int mSocket) : mSocket(mSocket) {}

int Client::getMSocket() const {
    return mSocket;
}
