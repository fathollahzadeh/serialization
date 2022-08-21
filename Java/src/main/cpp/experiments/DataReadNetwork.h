#ifndef CPP_DATAREADNETWORK_H
#define CPP_DATAREADNETWORK_H

#include "MachineInfo.h"
#include "Network.h"
#include "Client.h"
#include <thread>
#include <chrono>
#include "ObjectReader.h"
#include "ObjectWriter.h"

using namespace std;

//ObjectFileIndex
template<class T>
struct ObjectNetworkIndex {
    T *myObject;
    int clientIndex;

    virtual ~ObjectNetworkIndex() {
        delete myObject;
    }
};

//Ascending Sorter:
template<class T>
struct UniversalPointerComparatorAscending {
    bool operator()(T *a, T *b) {
        return *a < *b;
    }
};

//Descending Sorter:
template<class T>
struct UniversalPointerComparatorDescending {
    bool operator()(ObjectNetworkIndex<T> *a, ObjectNetworkIndex<T> *b) {
        if (*a->myObject < *b->myObject)
            return false;
        return true;
    }
};

template<class T>
class DataReadNetwork {
private:
    string config;
    string inDataPath;
    string method;
    string localMethod;

    Client *initClient(string ip, int port);

    bool isValid(int mSocket);


public:
    void runDataReader();

};

template<class T>
void DataReadNetwork<T>::runDataReader() {

    Network network(config);
    MachineInfo *machineInfo = network.getCurrentMachine();
    ObjectReader reader(inDataPath, localMethod);

    if (machineInfo->getNodeType() == LEAF) {
        T **list = new T *[machineInfo->getNrow()];
        int listSize = reader.readObjects(0, machineInfo->getNrow(), list);
        sort(list, list + listSize, UniversalPointerComparatorAscending<T>());

        ObjectWriter writer(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);
        Client *client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        for (T rd : list)
            writer.writeObjectToNetworkPage(rd, client.dos, client.dis);

        writer.flushToNetwork(client.dos, client.dis);
        client.socket.close();

    }
}

template<class T>
Client* DataReadNetwork<T>::initClient(string ip, int port) {
    bool flag = false;
    int mSocket;
    sockaddr_in mAddr;
    //Socket socket;
    Client *client = nullptr;
    for (int i = 0; i < 10 && !flag; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (!isValid())
            throw std::runtime_error("Client can't start (mSocket is not valid) >> " + ip + ":" + to_string(port));

        int on = 1;
        if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) == -1)
            throw std::runtime_error("Client can't start (setsockopt = -1) >> " + ip + ":" + to_string(port));

        mAddr.sin_family = AF_INET;
        mAddr.sin_port = htons(port);

        int status = inet_pton(AF_INET, ip.c_str(), &mAddr.sin_addr);
        if (errno == EAFNOSUPPORT)
            throw std::runtime_error("EAFNOSUPPORT ? >> " + ip + ":" + to_string(port));

        status = ::connect(mSocket, (sockaddr * ) & mAddr, sizeof(mAddr));
        if (status == 0){
            flag = true;
            client = new Client(mSocket);
            break;
        }
    }
    if (!flag)
        throw std::runtime_error("Client can't start >> " + ip + ":" + to_string(port));
    else {
        return client;
    }
}

template<class T>
bool DataReadNetwork<T>::isValid(int mSocket) {
    return mSocket != -1;
}


#endif //CPP_DATAREADNETWORK_H
