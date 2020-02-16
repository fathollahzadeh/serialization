//
// Created by saeed on 06.01.20.
//

#ifndef TWITTER_NETWORKCLIENT_H
#define TWITTER_NETWORKCLIENT_H

#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <FileHandler.h>
#include <FileHandler.cpp>
#include <LogFileHandler.h>

using namespace std;

template<class T>
class NetworkClient {

private:

    string fileName;

    int serializationType;

    long numOfObjects;

    int portNumber;

    string hostName;

    //Defile objects from serialization types:
    FileHandler<T> *fileHandler;

    //Network Experiments:
    long networkPageSize;

    LogFileHandler *logFileHandler;

    int ioType;//1: RAM, 2: Disk

    vector<T *> objectList;


public:

    NetworkClient();

    virtual ~NetworkClient();

    NetworkClient(string fileName, int serializationType, long numOfobjects, string hostName, int portNumber,
                  long networkPageSize, int ioType);

    void runTheNetworkClient();
};

template<class T>
void NetworkClient<T>::runTheNetworkClient() {

    // Run the network client from the RAM
    if (this->ioType == 1) {
        fileHandler->getObjectsFromFile(0, this->numOfObjects, objectList);
        cout << "Client: Objects are ready in RAM." << endl;
    }

    bool flag = false;
    while (true) {
        try {

            ClientSocket client_socket(this->hostName, this->portNumber);

            try {
                //Create a 20MB page:
                char *longBuffer;
                longBuffer = new char[2 * this->networkPageSize];

                //Send start code first: Goal is to let them know "Client" is up:
                long startCode = 1;
                memcpy(longBuffer, &startCode, sizeof(startCode));
                client_socket.write(longBuffer, sizeof(startCode));

                //Receive "GO":
                client_socket.read(longBuffer, sizeof(long));
                memcpy(&startCode, longBuffer, sizeof(long));
                if (startCode != 0) {
                    throw invalid_argument("ERROR: \"GO\" signal mismatch!");
                }

                long totalPageCount = 0;
                //if io type read data from disk and then send:
                if (this->ioType == 2) {
                    totalPageCount =fileHandler->getNetworkPageCount(numOfObjects);
                    cout << "Pages to be sent: " << totalPageCount << endl;
                } else
                    cout << "Pages to be sent: Unknown" << endl;

                int startIndex = 0;
                int localPageCount = 0;
                long pageSize=0;
                while (true) {
                    //Send a "1":
                    startCode = 1;
                    memcpy(longBuffer, &startCode, sizeof(startCode));
                    client_socket.write(longBuffer, sizeof(startCode));

                    // if io type is RAM:
                    if (ioType == 1) {
                        startIndex = fileHandler->getNextNetworkPage(objectList, startIndex, this->numOfObjects,longBuffer);
                    }
                    // if io type is Disk:
                    else if(ioType==2){
                        pageSize=fileHandler->getNextNetworkPage(longBuffer);
                    }


                    client_socket.write(longBuffer, networkPageSize);

                    //Print info:
                    cout << "Sending page ID = " << localPageCount << endl;
                    localPageCount++;

                    // break Out: Done:
                    if ((this->ioType==1 && startIndex >= this->numOfObjects)||(this->ioType==2 && (localPageCount>=totalPageCount||pageSize==0))) {
                        break;
                    }
                }
                //Termination Signal: Send a "0":
                startCode = 0;
                memcpy(longBuffer, &startCode, sizeof(startCode));
                client_socket.write(longBuffer, sizeof(startCode));

                //Free the buffer:
                delete[] longBuffer;

                //Everything done:
                flag = true;
            }
            catch (SocketException &) {}

        }
        catch (SocketException &e) {
            cout << "Exception was caught:" << e.description() << "\n";
            sleep(10);
        }

        if (flag) {
            break;
        }
    }
}

template<class T>
NetworkClient<T>::NetworkClient() {}

template<class T>
NetworkClient<T>::~NetworkClient() {}

template<class T>
NetworkClient<T>::NetworkClient(string fileName, int serializationType, long numOfObjects,
                                string hostName, int portNumber, long networkPageSize, int ioType) {

    this->fileName = fileName;
    this->serializationType = serializationType;
    this->numOfObjects = numOfObjects;
    this->hostName = hostName;
    this->portNumber = portNumber;
    this->networkPageSize = networkPageSize;
    this->ioType = ioType;
    this->fileHandler = new FileHandler<T>(this->fileName, this->serializationType);
    fileHandler->prepareToRead();
    fileHandler->setNetworkPageSize(this->networkPageSize);

    this->logFileHandler = new LogFileHandler(
            "bin/benchmark/networkclientfromram/result_cpp_readobjects_" + to_string(numOfObjects) + ".txt");
}

#endif //TWITTER_NETWORKCLIENT_H
