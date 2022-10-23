#ifndef CPP_DATAREADNETWORK_H
#define CPP_DATAREADNETWORK_H

#include "MachineInfo.h"
#include "Network.h"
#include "Client.h"
#include "Server.h"
#include <thread>
#include <chrono>
#include "ObjectReader.h"
#include "ObjectWriter.h"
#include "readerwriterqueue.h"
#include <cmath>
#include <queue>
#include <utility>

using namespace moodycamel;
using namespace std;

//ObjectFileIndex
template<class T>
struct ObjectNetworkIndex {
    T *myObject;
    int clientIndex;

    virtual ~ObjectNetworkIndex() {
        //if (myObject != nullptr)
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
    string outDataPath;
    string method;
    string plan;
    bool *statuses;
    BlockingReaderWriterQueue<vector<T *>> **queues;
    int numberOfClients;

    Client *initClient(string ip, int port);

    void NetworkReadTask(ObjectReader *reader, Socket *client, int id);

    void LocalReadTask(ObjectReader *reader, int nrow, int id);

    void ExternalSortTask(ObjectWriter *writer, bool onDisk, Client *client);

public:
    DataReadNetwork(string config, string inDataPath, string outDataPath, string method, string plan);

    void runDataReader();
};

template<class T>
void DataReadNetwork<T>::runDataReader() {
    Network network(config);
    MachineInfo *machineInfo = network.getCurrentMachine();
    ObjectReader *reader = new ObjectReader(inDataPath, method);
    if (machineInfo->getNodeType() == LEAF) {
        Client *client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        T **list = new T *[machineInfo->getNrow()];
        int listSize = reader->readObjects(0, machineInfo->getNrow(), list);
        sort(list, list + listSize, UniversalPointerComparatorAscending<T>());
        ObjectWriter writer(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);

        for (int i = 0; i < listSize; ++i)
            writer.writeObjectToNetworkPage(list[i], client);
        if (reader->getMethod() != INPLACE) {
            for (int i = 0; i < listSize; ++i) {
                delete list[i];
            }
        } else{
            for (int i = 0; i < listSize; ++i) {
                char *tbuffer = (char *) list[i];
                delete[] tbuffer;
            }
        }
        writer.flushToNetwork(client);
        delete[] list;
        delete client;
    } else if (machineInfo->getNodeType() == MIDDLE) {
        Client *client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        numberOfClients = machineInfo->getLeaves().size() + 1;
        Server server(machineInfo->getPort(), numberOfClients - 1);
        queues = new BlockingReaderWriterQueue<vector<T *>> *[numberOfClients];
        statuses = new bool[numberOfClients];
        vector<thread> pool;
        Socket **clients = new Socket*[numberOfClients -1];

        for (int i = 0; i < machineInfo->getLeaves().size(); i++) {
            Socket *client = new Socket();
            server.accept(client);
            ObjectReader *clientReader = new ObjectReader(method);
            queues[i] = new BlockingReaderWriterQueue<vector<T *>>(NETWORK_CLIENT_QUEUE_SIZE);
            pool.push_back(std::thread(&DataReadNetwork<T>::NetworkReadTask, this, clientReader, client, i));
            clients[i] = client;
        }
        queues[numberOfClients - 1] = new BlockingReaderWriterQueue<vector<T *>>(NETWORK_CLIENT_QUEUE_SIZE);
        pool.push_back(std::thread(&DataReadNetwork<T>::LocalReadTask, this, reader, machineInfo->getNrow(), numberOfClients - 1));
        ObjectWriter writer(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);
        ExternalSortTask(&writer, false, client);

        for (auto &th: pool) {
            th.join();
        }

        for (int i = 0; i < numberOfClients -1 ; ++i) {
            clients[i]->writeACK();
            delete clients[i];
        }
        delete[] clients;

        delete client;
        for (int i = 0; i < numberOfClients; ++i) {
            delete queues[i];
        }
        delete queues;

    } else if (machineInfo->getNodeType() == ROOT) {
        numberOfClients = machineInfo->getLeaves().size() + 1;
        Server server(machineInfo->getPort(), numberOfClients - 1);
        queues = new BlockingReaderWriterQueue<vector<T *>> *[numberOfClients];
        statuses = new bool[numberOfClients];
        vector<thread> pool;
        Socket **clients = new Socket*[numberOfClients -1];

        //Socket socket;
        for (int i = 0; i < numberOfClients -1; i++) {
            Socket *client = new Socket();
            server.accept(client);
            ObjectReader *clientReader = new ObjectReader(method);
            queues[i] = new BlockingReaderWriterQueue<vector<T *>>(NETWORK_CLIENT_QUEUE_SIZE);
            pool.push_back(std::thread(&DataReadNetwork<T>::NetworkReadTask, this, clientReader, client, i));
            clients[i] = client;
        }
        queues[numberOfClients - 1] = new BlockingReaderWriterQueue<vector<T *>>(NETWORK_CLIENT_QUEUE_SIZE);
        pool.push_back(std::thread(&DataReadNetwork<T>::LocalReadTask, this, reader, machineInfo->getNrow(), numberOfClients - 1));

        if (strcasecmp(plan.c_str(), "d2d") == 0 || strcasecmp(plan.c_str(), "m2d") == 0) {
            ObjectWriter writer(outDataPath, method, machineInfo->getTotalNRow());
            ExternalSortTask(&writer, true, nullptr);
        }
        else
            ExternalSortTask(nullptr, false, nullptr);

        for (auto &th: pool) {
            th.join();
        }
        for (int i = 0; i < numberOfClients -1 ; ++i) {
            clients[i]->writeACK();
            delete clients[i];
        }
        delete[] clients;

        for (int i = 0; i < numberOfClients; ++i) {
            delete queues[i];
        }
        delete queues;
    }
    delete machineInfo;
    delete reader;
}

template<class T>
Client *DataReadNetwork<T>::initClient(string ip, int port) {
    for (int i = 0; i < 1000; i++) {
        try {
            Client *client = new Client(ip, port);
            return client;
        } catch (const exception &e) {}
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    throw std::runtime_error("Client can't start >> " + ip + ":" + to_string(port));
}

template<class T>
void DataReadNetwork<T>::NetworkReadTask(ObjectReader *reader, Socket *client, int id) {
    statuses[id] = true;
    while (true) {
        client->writeACK();
        int pageSize = client->readInt();
        if (pageSize == -1) {
            break;
        }
        char *buffer = new char[pageSize];
        client->read(buffer, pageSize);
        vector<T *> list;
        reader->deSerializeNetworkBuffer(buffer, pageSize, list);
        delete[] buffer;
        while (!queues[id]->try_enqueue(list));
    }
    statuses[id] = false;
}

template<class T>
void DataReadNetwork<T>::LocalReadTask(ObjectReader *reader, int nrow, int id) {
    statuses[id] = true;
    T **list = new T *[nrow];
    reader->readObjects(0, nrow, list);
    sort(list, list + nrow, UniversalPointerComparatorAscending<T>());
    int chunks = (int) ceil((double) nrow / NETWORK_LOCAL_READ_LENGTH);

    for (int i = 0; i < chunks & i * NETWORK_LOCAL_READ_LENGTH < nrow; i++) {
        vector<T *> tmpList;
        for (int j = i * NETWORK_LOCAL_READ_LENGTH; j < min((i + 1) * NETWORK_LOCAL_READ_LENGTH, nrow); j++) {
            tmpList.push_back(list[j]);
        }
        while (!queues[id]->try_enqueue(tmpList));
    }
    statuses[id] = false;
}

template<class T>
void DataReadNetwork<T>::ExternalSortTask(ObjectWriter *writer, bool onDisk, Client *client) {
    priority_queue<ObjectNetworkIndex<T> *, vector<ObjectNetworkIndex<T> *>, UniversalPointerComparatorDescending<T> > queue;
    long *pageObjectCounter = new long[numberOfClients];
    vector<T *> dataList;

    // reading objects from the first pages and adding them to a priority queue
    for (int i = 0; i < numberOfClients; i++) {
        vector<T *> listReadFromFile;
        queues[i]->wait_dequeue(listReadFromFile);
        pageObjectCounter[i] = listReadFromFile.size();
        for (T *rd: listReadFromFile) {
            ObjectNetworkIndex<T> *objectNetworkIndex = new ObjectNetworkIndex<T>();
            objectNetworkIndex->clientIndex = i;
            objectNetworkIndex->myObject = rd;
            queue.push(objectNetworkIndex);
        }
    }
    cout << "Network External Sort: First page reading is done! " << endl;
    int c = 0;

    while (!queue.empty()) {
        ObjectNetworkIndex<T> *tmpObjectNetworkIndex = queue.top();
        queue.pop();
        int clientNumber = tmpObjectNetworkIndex->clientIndex;

        // reduce the number of objects read from that file.
        pageObjectCounter[clientNumber] =  pageObjectCounter[clientNumber] - 1;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if (pageObjectCounter[clientNumber] == 0) {
            vector<T *> listReadFromFile;
            while (statuses[clientNumber] && listReadFromFile.empty()){
                queues[clientNumber]->try_dequeue(listReadFromFile);
            }
            if (!listReadFromFile.empty()) {
                pageObjectCounter[clientNumber] = listReadFromFile.size();
                for (T *rd: listReadFromFile) {
                    ObjectNetworkIndex<T> *objectNetworkIndex = new ObjectNetworkIndex<T>();
                    objectNetworkIndex->clientIndex = clientNumber;
                    objectNetworkIndex->myObject = rd;
                    queue.push(objectNetworkIndex);
                }
            }
        }

        if (writer != nullptr) {
            if (onDisk) {writer->writeObjectToFile(tmpObjectNetworkIndex->myObject); c++;}
            else writer->writeObjectToNetworkPage(tmpObjectNetworkIndex->myObject, client);

        } else
            dataList.push_back(tmpObjectNetworkIndex->myObject);
        delete tmpObjectNetworkIndex;
    }
    cout << "Network External Sort: Done! c="<< c << endl;
    if (writer != nullptr) {
        if (onDisk) writer->flush();
        else writer->flushToNetwork(client);
    }

    delete[] pageObjectCounter;
}

template<class T>
DataReadNetwork<T>::DataReadNetwork(string config,
                                    string inDataPath,
                                    string outDataPath,
                                    string method,
                                    string plan):
        config(std::move(config)),
        inDataPath(std::move(inDataPath)),
        outDataPath(std::move(outDataPath)),
        method(std::move(method)),
        plan(std::move(plan)) {}

#endif //CPP_DATAREADNETWORK_H
