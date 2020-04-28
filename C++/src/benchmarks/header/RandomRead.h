//
// Created by saeed on 11/17/19.
//

#ifndef TWITTER_RANDOMREAD_H
#define TWITTER_RANDOMREAD_H

#include <vector>
#include <iostream>
#include <FileHandler.h>
#include <FileHandler.cpp>
#include <LogFileHandler.h>

using namespace std;

template<class T>
class RandomRead {
private:
    string fileName;

    int serializationType;

    long cuntToRead;

    //Vector variable for store random variables
    vector<long> objectIndexes;

    LogFileHandler *logFileHandler;

    bool taskset;
public:
    void setObjectIndexes(const vector<long> &objectIndexes);


public:

    RandomRead();

    virtual ~RandomRead();

    RandomRead(string fileName, int serializationType, long cuntToRead, int round,bool taskset);

    void runTheRandomRead();

};

template<class T>
void RandomRead<T>::runTheRandomRead() {

    //Defile objects from serialization types:
    FileHandler<T> *fileHandler = new FileHandler<T>(fileName, serializationType);

    fileHandler->prepareToRead();

    // start of time calculation
    auto tmpTime = chrono::steady_clock::now();

     vector<T *> objectList;
    for (long j = 0; j < cuntToRead; ++j) {
        fileHandler->getObjectsFromFile(objectIndexes.at(j), 1, objectList);
    }

    double elapsedSeconds = chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

    // add times to the log file
    this->logFileHandler->addLog(serializationType, false, "TweetStatus", fileHandler->getIoTime(), elapsedSeconds,taskset);
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
RandomRead<T>::RandomRead(string fileName, int serializationType, long cuntToRead, int round,bool taskset) {
    this->fileName = fileName;
    this->serializationType = serializationType;
    this->cuntToRead = cuntToRead;
    this->taskset=taskset;
    this->logFileHandler = new LogFileHandler(
            "bin/benchmark/readobjects/result_cpp_readobjects_" + to_string(cuntToRead) + "_" + to_string(round) +
            ".txt");
}

template<class T>
RandomRead<T>::RandomRead() {}

template<class T>
RandomRead<T>::~RandomRead() {
    delete logFileHandler;
}

template<class T>
void RandomRead<T>::setObjectIndexes(const vector<long> &objectIndexes) {
    RandomRead::objectIndexes = objectIndexes;
}


#endif //TWITTER_RANDOMREAD_H
