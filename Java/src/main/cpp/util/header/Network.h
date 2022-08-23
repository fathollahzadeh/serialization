#ifndef CPP_NETWORK_H
#define CPP_NETWORK_H

#include <map>
#include <iostream>
#include "MachineInfo.h"
#include <fstream>
#include <sstream>
#include <cstring>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

class Network {

private:
    map<string, MachineInfo*> machineInfos;

    void readConfigFile(const string &config);

    int computeNRow(MachineInfo *node);

public:

    Network(const string &config);

    virtual ~Network();

    MachineInfo *getCurrentMachine();

};


#endif //CPP_NETWORK_H
