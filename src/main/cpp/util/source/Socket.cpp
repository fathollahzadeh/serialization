#include "Socket.h"

Socket::Socket() {
    mSocket = -1;
    memset(&mAddr, 0, sizeof(mAddr));
}

Socket::~Socket() {
    if (isValid())
        close(mSocket);
}

bool Socket::create() {
    mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (!isValid())
        return false;

    // TIME_WAIT - argh
    int on = 1;
    if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) == -1)
        return false;
    return true;
}

bool Socket::bind(int port) {
    if (!isValid()) {
        return false;
    }
    bzero((char *) &mAddr, sizeof(mAddr));
    mAddr.sin_family = AF_INET;
    mAddr.sin_addr.s_addr = INADDR_ANY;
    mAddr.sin_port = htons(port);

    int bindReturn = ::bind(mSocket, (struct sockaddr *) &mAddr, sizeof(mAddr));

    if (bindReturn == -1) {
        return false;
    }

    return true;
}

bool Socket::accept(Socket *newSocket) const {
    int addrLength = sizeof(mAddr);
    newSocket->mSocket = ::accept(mSocket, (sockaddr * ) & mAddr, (socklen_t * ) & addrLength);
    if (newSocket->mSocket <= 0)
        return false;
    else
        return true;
}

bool Socket::listen(int count) const {
    if (!isValid()) {
        return false;
    }
    int listenReturn = ::listen(mSocket, count);
    if (listenReturn == -1) {
        return false;
    }
    return true;
}

bool Socket::connect(const string& ip, int port) {
    if (!isValid()) return false;
    struct hostent *host;
    host = gethostbyname(ip.c_str());
    if (host == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        return false;
    }
    bzero((char *) &mAddr, sizeof(mAddr));
    mAddr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&mAddr.sin_addr.s_addr, host->h_length);
    mAddr.sin_port = htons(port);
    int status = ::connect(mSocket, (struct sockaddr *) &mAddr,sizeof(mAddr));
    if (status == 0)
        return true;
    else
        return false;
}

void Socket::write(char *buffer, long contentSize) {
    //New Code:
    long bytesWritten = 0;
    long status = 0;
    while (bytesWritten < contentSize) {
        status = ::write(mSocket, buffer + bytesWritten, contentSize - bytesWritten);
        bytesWritten += status;

        //Error Handling:
        if (!status)
            throw std::runtime_error("Could not write to socket.");;
    }
    if (bytesWritten != contentSize)
        throw std::runtime_error("ClientSocket: Mismatch in write()");

}

void Socket::read(char *buffer, long contentSize) {
    //New Code:
    long bytesRead = 0;
    long status = 0;
    while (bytesRead < contentSize) {
        cout<<" 8888888888888 "<<endl;
        status = ::read(mSocket, buffer + bytesRead, contentSize - bytesRead);
        cout<<"000000000000000000000000000 +++ "<<status<<endl;
        bytesRead += status;

        //Error Handling:
        if (!status)
            throw std::runtime_error("Could not read from socket.");
    }
    if (bytesRead != contentSize) {
        throw std::runtime_error("ClientSocket: Mismatch in read()");
    }
}

bool Socket::isValid() const {
    return mSocket != -1;;
}


bool Socket::readACK() {
    cout<< "+++++++++++++?  readACK()"<<endl;
    char *ack = new char[1];
    read(ack, 1);
    if (ack[0] != '1') {
        throw std::runtime_error("Can't read correct ACK from socket !");
    }
    return true;
}

bool Socket::writeACK() {
    char *ack = new char[1];
    ack[0] = '1';
    write(ack, 1);
    return true;
}

void Socket::write(int value) {
    char *buf = new char[sizeof(value)];
    memcpy(buf, &value, sizeof(value));
    write(buf, sizeof(value));
}

int Socket::readInt() {
    char *val = new char[sizeof(int)];
    read(val, sizeof(int));
    int intVal;
    memcpy(&intVal, val, sizeof(intVal));
    return intVal;
}
