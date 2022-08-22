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
#include "math.h"
#include <queue>

using namespace moodycamel;
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
    int methodID;
    bool **status;
    BlockingReaderWriterQueue <vector<T*>> **queues;
    int numberOfClients;

    Client initClient(string ip, int port);

    void NetworkReadTask(ObjectReader *reader, Socket *client, BlockingReaderWriterQueue <vector<T*>> *queues ,bool *status);

    void LocalReadTask(ObjectReader *reader, int nrow, BlockingReaderWriterQueue <vector<T*>> *queues ,bool *status);

    void ExternalSortTask(ObjectWriter *writer, bool onDisk, Client * client);

public:
    void runDataReader();

};

template<class T>
void DataReadNetwork<T>::runDataReader() {

    Network network(config);
    MachineInfo *machineInfo = network.getCurrentMachine();
    ObjectReader reader(inDataPath, localMethod);
    methodID = reader.getMethod();

    if (machineInfo->getNodeType() == LEAF) {
        T **list = new T *[machineInfo->getNrow()];
        int listSize = reader.readObjects(0, machineInfo->getNrow(), list);
        sort(list, list + listSize, UniversalPointerComparatorAscending<T>());

        ObjectWriter writer(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);
        Client client = initClient(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        for (T rd : list)
            writer.writeObjectToNetworkPage(rd, client);

        writer.flushToNetwork(client);

    } else if (machineInfo->getNodeType() == MIDDLE) {
        Server server(machineInfo->getPort());
        //server.setSoTimeout(Const.NETWORK_TIMEOUT);
        Client client(machineInfo->getRoot()->getIp(), machineInfo->getPort());
        numberOfClients = machineInfo->getLeaves().size()+1;
        queues = new BlockingReaderWriterQueue <vector<T*>>*[numberOfClients];

        status = new bool *[numberOfClients];

        vector<thread> pool;
        for (int i = 0; i < machineInfo->getLeaves().size(); i++) {
            Socket *client;
            server.accept(client);
            ObjectReader *clientReader = new ObjectReader(method);
            queues[i] = new BlockingReaderWriterQueue <vector<T*>>(NETWORK_CLIENT_QUEUE_SIZE);
            pool.push_back(std::thread(NetworkReadTask, reader, client, queues[i], &status[i]));
        }
        pool.push_back(std::thread(LocalReadTask, reader, machineInfo->getNrow(),
                                   queues[numberOfClients -1], &status[numberOfClients -1]));


        ObjectWriter *writer = new ObjectWriter(method, machineInfo->getTotalNRow(), NETWORK_PAGESIZE);
        // add external sort task
        tasks.add(new ExternalSortTask(dataTasks, writer, false, client.dis, client.dos));


    }
}

template<class T>
Client DataReadNetwork<T>::initClient(string ip, int port) {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        try {
            Client client(ip, port);
            return client;
        } catch (const exception& e) { }
    }
    throw SocketException("Client can't start >> " + ip + ":" + to_string(port));
}

template<class T>
void DataReadNetwork<T>::NetworkReadTask(ObjectReader *reader, Socket *client, BlockingReaderWriterQueue <vector<T*>> *queue, bool *status) {
    *status = true;
    while (true) {
        client->writeACK();
        int pageSize =  client->readInt();
        if (pageSize == -1) {
            client->writeACK();
            break;
        }
        char *buffer = new char[pageSize];
        client->read(buffer, pageSize);

        vector<T*> list;
        reader->deSerializeNetworkBuffer(buffer+sizeof(int), pageSize, &list);
        queue->enqueue(list);
    }
    *status = false;
    delete client;
}

template<class T>
void DataReadNetwork<T>::LocalReadTask(ObjectReader *reader, int nrow, BlockingReaderWriterQueue <vector<T*>> *queue ,bool *status) {
    *status = true;
    TweetStatus **list = new TweetStatus *[nrow];
    int rdSize = reader->readObjects(0, nrow, list);
    sort(list, list + nrow, UniversalPointerComparatorAscending<T>());
    int chunks = (int) ceil((double) nrow / NETWORK_LOCAL_READ_LENGTH);

    for (int i = 0; i < chunks & i * NETWORK_LOCAL_READ_LENGTH < nrow; i++) {
        vector<T*> tmpList;
        for (int j = i * NETWORK_LOCAL_READ_LENGTH; j < min((i + 1) * NETWORK_LOCAL_READ_LENGTH, nrow); j++) {
            tmpList.add(list[j]);
        }
        queue->enqueue(tmpList);
    }
    *status = false;
}

template<class T>
void DataReadNetwork<T>::ExternalSortTask(ObjectWriter *writer, bool onDisk, Client *client) {
    priority_queue<ObjectNetworkIndex<T> *, vector < ObjectNetworkIndex<T> *>, UniversalPointerComparatorDescending<T> > queue;
    long *pageObjectCounter = new long[numberOfClients];

    // reading objects from the first pages and adding them to a priority queue
    for (int i = 0; i < numberOfClients; i++) {
        BlockingReaderWriterQueue <vector<T*>>* q = queues[i];
        vector<T*> listReadFromFile;
        q->wait_dequeue(&listReadFromFile);
        pageObjectCounter[i] = listReadFromFile.size();
        for (T* rd : listReadFromFile) {
            ObjectNetworkIndex<T> *objectNetworkIndex = new ObjectNetworkIndex<T>();
            objectNetworkIndex->clientIndex = i;
            objectNetworkIndex->myObject = rd;
            queue.push(objectNetworkIndex);
        }
    }
    cout<<"Network External Sort: First page reading is done! "<<endl;

    while (!queue.isEmpty()) {
        ObjectNetworkIndex<T> *tmpObjectNetworkIndex = queue.top();
        queue.pop();
        int clientNumber = tmpObjectNetworkIndex->getClientIndex();

        // reduce the number of objects read from that file.
        pageObjectCounter[clientNumber]--;

        // If needed load more objects from files.
        // if zero load the next page from file and add objects.
        if (pageObjectCounter[clientNumber] == 0) {
            vector<T*> *listReadFromFile;
            BlockingReaderWriterQueue <vector<T*>>* q = queues[clientNumber];
            if (q-> !tasks.get(clientNumber).queue.isEmpty()) {
                listReadFromFile = tasks.get(clientNumber).queue.take();
            } else {
                while (tasks.get(clientNumber).status && tasks.get(clientNumber).queue.isEmpty()) ;
                if (!tasks.get(clientNumber).queue.isEmpty()) {
                    listReadFromFile = tasks.get(clientNumber).queue.take();
                }
            }
            if (listReadFromFile != null) {
                pageObjectCounter[clientNumber] = listReadFromFile.size();
                for (RootData rd : listReadFromFile) {
                    ObjectNetworkIndex objectNetworkIndex = new ObjectNetworkIndex(clientNumber, rd);
                    queue.add(objectNetworkIndex);
                }
            }
        }
        if (writer !=null) {
            if (onDisk) writer.writeObjectToFile(tmpObjectNetworkIndex.myObject);
            else writer.writeObjectToNetworkPage(tmpObjectNetworkIndex.myObject, dos, dis);
        }
        else
            this.dataList.add(tmpObjectNetworkIndex.myObject);
    }
    logger.info("Network External Sort: Done!");
    if (writer != null) {
        if (onDisk) writer.flush();
        else writer.flushToNetwork(dos, dis);
    }




}


#endif //CPP_DATAREADNETWORK_H
