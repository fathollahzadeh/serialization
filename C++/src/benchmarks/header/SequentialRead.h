//
// Created by saeed on 11/6/19.
//

#ifndef C_SequentialRead_H
#define C_SequentialRead_H

#include <iostream>
#include <FileHandler.h>
#include <FileHandler.cpp>
#include <LogFileHandler.h>

using namespace std;

template<class T>
class SequentialRead {

private:
    string fileName;

    int serializationType;

    long from;

    long cuntToRead;

    LogFileHandler *logFileHandler;

    bool taskset;

public:

    SequentialRead(string fileName, int serializationType, long from, long cuntToRead, int round,bool taskset);

    SequentialRead();

    virtual ~SequentialRead();

    void runTheSequentialRead();

};

template<class T>
void SequentialRead<T>::runTheSequentialRead() {

    //Defile objects from serialization types:
    FileHandler<T> *fileHandler = new FileHandler<T>(fileName, serializationType);

    fileHandler->prepareToRead();

    // start of time calculation
    auto tmpTime = chrono::steady_clock::now();

    vector<T *> objectList;
    fileHandler->getObjectsFromFile(from, cuntToRead, objectList);
    double elapsedSeconds = chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

     // add times to the log file
    this->logFileHandler->addLog(false,serializationType, true, "TweetStatus", fileHandler->getIoTime(), elapsedSeconds,taskset);
    this->logFileHandler->flushLogFile();

    // free memory:
    for (long i = 0; i < cuntToRead; ++i){
         if (serializationType!=2){
            delete objectList.at(i);
        } else{
            char * tbuffer=(char *)objectList.at(i);
            delete[] tbuffer;
        }
    }
    fileHandler->getObjectsFromFileFlush();

    delete fileHandler;
}

template<class T>
SequentialRead<T>::~SequentialRead() {

    delete logFileHandler;
}

template<class T>
SequentialRead<T>::SequentialRead() {}

template<class T>
SequentialRead<T>::SequentialRead(string fileName, int serializationType, long from, long cuntToRead, int round,bool taskset) {
    this->fileName = fileName;
    this->serializationType = serializationType;
    this->cuntToRead = cuntToRead;
    this->taskset=taskset;
    this->from = from;
    this->logFileHandler = new LogFileHandler(
            "bin/benchmark/readobjects/result_cpp_readobjects_" + to_string(cuntToRead) + "_" + to_string(round) +
            ".txt");
}


#endif //C_SequentialRead_H
