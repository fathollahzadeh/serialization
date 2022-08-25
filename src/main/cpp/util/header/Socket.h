#ifndef CPP_SOCKET_H
#define CPP_SOCKET_H

#include "Const.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

class Socket {

protected:
    int mSocket;
    sockaddr_in mAddr;

public:

    Socket();

    virtual ~Socket();

    // Server initialization
    bool create();

    bool bind(int port);

    bool listen(int count) const;

    bool accept(Socket *newSocket) const;

    // Client initialization
    bool connect(const string& ip, int port);

    // Data Transimission
    void write(char *buffer, long contentSize);

    void write(int value);

    void read(char *buffer, long contentSize);

    int readInt();

    bool readACK();

    bool writeACK();

    bool isValid() const;

};


#endif //CPP_SOCKET_H
