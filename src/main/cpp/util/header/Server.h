#ifndef CPP_SERVER_H
#define CPP_SERVER_H

#include "Socket.h"

using namespace std;

class Server: public Socket{

private:

public:
    Server(int port);

    ~Server() override;

};

#endif //CPP_SERVER_H
