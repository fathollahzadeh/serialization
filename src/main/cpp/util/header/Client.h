#ifndef CPP_CLIENT_H
#define CPP_CLIENT_H

#include "Socket.h"

using namespace std;

class Client: public Socket {
private:

public:

    Client(string ip, int port);

    virtual ~Client();

};


#endif //CPP_CLIENT_H
