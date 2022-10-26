#ifndef CPP_DATAREADNETWORKIO_H
#define CPP_DATAREADNETWORKIO_H

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

template<class T>
class DataReadNetworkIO {
private:
    string config;
    string inDataPath;
    string outDataPath;
    string method;
    string plan;
    bool *statuses;
    BlockingReaderWriterQueue<char *> **queues;
    int numberOfClients;

    Client *initClient(string ip, int port);

    void NetworkReadTask(ObjectReader *reader, Socket *client, int id);

    void LocalReadTask(ObjectReader *reader, int nrow, int id);

    void ExternalSortTask(ObjectWriter *writer, bool onDisk, Client *client);

public:
    DataReadNetworkIO(string config, string inDataPath, string outDataPath, string method, string plan);

    void runDataReader();
};

template<class T>
void DataReadNetworkIO<T>::runDataReader() {
    Network network(config);
    MachineInfo *machineInfo = network.getCurrentMachine();
    ObjectReader *reader = new ObjectReader(inDataPath, method);
    int QUEUE_SIZE = ceil(NETWORK_CLIENT_QUEUE_SIZE * ((double )PAGESIZE/NETWORK_PAGESIZE));

    if (machineInfo->getNodeType() == LEAF) {
        Client *client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        char ** pages = new char*[reader->getNetworkPageCount()];
        reader->readAllPages(pages);
        ObjectWriter writer(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);
        for (int i = 0; i < reader->getNetworkPageCount(); ++i) {
            writer.writeToNetworkPage(pages[i], client);
            delete[] pages[i];
        }

        // flush client
        client->readACK();
        client->write(-1);
        client->readACK();

        // free memory
        delete[] pages;
        delete client;
    } else if (machineInfo->getNodeType() == MIDDLE) {
        Client *client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        numberOfClients = machineInfo->getLeaves().size() + 1;
        Server server(machineInfo->getPort(), numberOfClients - 1);
        queues = new BlockingReaderWriterQueue<char *> *[numberOfClients];
        statuses = new bool[numberOfClients];
        vector<thread> pool;
        Socket **clients = new Socket*[numberOfClients -1];

        for (int i = 0; i < machineInfo->getLeaves().size(); i++) {
            Socket *client = new Socket();
            server.accept(client);
            ObjectReader *clientReader = new ObjectReader(method);
            queues[i] = new BlockingReaderWriterQueue<char *>(QUEUE_SIZE);
            pool.push_back(std::thread(&DataReadNetworkIO<T>::NetworkReadTask, this, clientReader, client, i));
            clients[i] = client;
        }
        queues[numberOfClients - 1] = new BlockingReaderWriterQueue<char *>(QUEUE_SIZE);
        pool.push_back(std::thread(&DataReadNetworkIO<T>::LocalReadTask, this, reader, machineInfo->getNrow(), numberOfClients - 1));
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
        queues = new BlockingReaderWriterQueue<char *> *[numberOfClients];
        statuses = new bool[numberOfClients];
        vector<thread> pool;
        Socket **clients = new Socket*[numberOfClients -1];

        //Socket socket;
        for (int i = 0; i < numberOfClients -1; i++) {
            Socket *client = new Socket();
            server.accept(client);
            ObjectReader *clientReader = new ObjectReader(method);
            queues[i] = new BlockingReaderWriterQueue<char *>(NETWORK_CLIENT_QUEUE_SIZE);
            pool.push_back(std::thread(&DataReadNetworkIO<T>::NetworkReadTask, this, clientReader, client, i));
            clients[i] = client;
        }
        queues[numberOfClients - 1] = new BlockingReaderWriterQueue<char *>(NETWORK_CLIENT_QUEUE_SIZE);
        pool.push_back(std::thread(&DataReadNetworkIO<T>::LocalReadTask, this, reader, machineInfo->getNrow(), numberOfClients - 1));

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
Client *DataReadNetworkIO<T>::initClient(string ip, int port) {
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
void DataReadNetworkIO<T>::NetworkReadTask(ObjectReader *reader, Socket *client, int id) {
    statuses[id] = true;
    while (true) {
        client->writeACK();
        int pageSize = client->readInt();
        if (pageSize == -1) {
            break;
        }
        char *buffer = new char[pageSize+sizeof(int)];
        memcpy(buffer, &pageSize, sizeof(int));
        client->read(buffer+sizeof(int), pageSize);
        while (!queues[id]->try_enqueue(buffer));
    }
    statuses[id] = false;
}

template<class T>
void DataReadNetworkIO<T>::LocalReadTask(ObjectReader *reader, int nrow, int id) {
    statuses[id] = true;
    char ** pages = new char*[reader->getNetworkPageCount()];
    reader->readAllPages(pages);

    for (int i = 0; i < reader->getNetworkPageCount(); i++) {
       while (!queues[id]->try_enqueue(pages[i]));
    }
    statuses[id] = false;
}

template<class T>
void DataReadNetworkIO<T>::ExternalSortTask(ObjectWriter *writer, bool onDisk, Client *client) {
    // reading objects from the first pages and adding them to a priority queue
    bool flag;
    do {
        flag = false;
        for (int i = 0; i < numberOfClients; i++) {
            while (statuses[i] && queues[i]->peek() == nullptr);
            if (queues[i]->peek() != nullptr) {
                char *page = *queues[i]->peek();
                if (writer != nullptr) {
                    if (onDisk) writer->writeNetworkPageToFile(page);
                    else writer->writeToNetworkPage(page, client);
                }
                queues[i]->pop();
                flag = true;
            }
        }
    } while (flag);

    cout << "Network External Sort Data Transfer: Done!" << endl;
    if (writer != nullptr) {
        if (onDisk) writer->flushNetworkPageWriter();
        else{
            client->readACK();
            client->write(-1);
            client->readACK();
        }
    }
}

template<class T>
DataReadNetworkIO<T>::DataReadNetworkIO(string config,
                                    string inDataPath,
                                    string outDataPath,
                                    string method,
                                    string plan):
        config(std::move(config)),
        inDataPath(std::move(inDataPath)),
        outDataPath(std::move(outDataPath)),
        method(std::move(method)),
        plan(std::move(plan)) {}

#endif //CPP_DATAREADNETWORKIO_H
