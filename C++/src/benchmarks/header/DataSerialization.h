//
// Created by saeed on 12/14/19.
//

#ifndef TWITTER_DATASERIALIZATION_H
#define TWITTER_DATASERIALIZATION_H

#include <iostream>
#include "rapidjson/document.h"
#include <iostream>
#include <fstream>
#include "TweetStatus.h"
#include "DataReader.h"
#include "FileHandler.h"
#include "FileHandler.cpp"
#include <TweetStatusProto.h>

using  namespace std;
template<class T>
class DataSerialization{

private:

    ifstream infile;
    string line;
    string inputFileName;
    string outFileName;
    int serializationType;

public:
    DataSerialization();

    DataSerialization(const string &inputFileName, const string &outFileName, int serializationType);

    virtual ~DataSerialization();

    void runTheDataSerialization();
};

template<class T>
void DataSerialization<T>::runTheDataSerialization() {

    ifstream infile;
    infile.open(inputFileName);

    // Define file handler for each serialization type:
    FileHandler<T> *fileHandler=new FileHandler<T>(outFileName,serializationType);
    fileHandler->prepareToWrite();


    DataReader dataReader;
    int l = 0;
    while (getline(infile, line)) {
        Document d;
        //Parse read data:
        d.Parse(line.c_str());

        //Convert json data to the TweetStatus Object:
        TweetStatus *tweet = dataReader.generateTweetObject(d);

        //Serialize the TweetStatus object and then write to file:
        fileHandler->appendObjectToFile(tweet);

        //Free memory:
        delete tweet;
    }
    infile.close();
    infile.clear();

    fileHandler->appendObjectToFileFlush();
    delete  fileHandler;

}

template<class T>
DataSerialization<T>::DataSerialization() {}

template<class T>
DataSerialization<T>::~DataSerialization() {

}

template<class T>
DataSerialization<T>::DataSerialization(const string &inputFileName, const string &outFileName, int serializationType)
        :inputFileName(inputFileName), outFileName(outFileName), serializationType(serializationType) {}

#endif //TWITTER_DATASERIALIZATION_H
