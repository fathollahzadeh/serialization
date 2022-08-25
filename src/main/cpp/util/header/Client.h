#ifndef CPP_CLIENT_H
#define CPP_CLIENT_H

#include "Socket.h"

using namespace std;

class Client: public Socket {
private:

public:

    Client(const string& ip, int port);

    ~Client() override;

};


#endif //CPP_CLIENT_H
