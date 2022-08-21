#ifndef CPP_CLIENT_H
#define CPP_CLIENT_H

#include <netinet/in.h>

using namespace std;
class Client {
private:
    int mSocket;
    sockaddr_in mAddr;
public:

    Client(int mSocket);

    Client(const sockaddr_in &mAddr);

    virtual ~Client();

    const sockaddr_in &getMAddr() const;

    int getMSocket() const;
};


#endif //CPP_CLIENT_H
