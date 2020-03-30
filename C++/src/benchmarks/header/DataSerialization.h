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
#include "readerwriterqueue.h"
#include <thread>

using namespace moodycamel;
using namespace std;

template<class T>
class DataSerialization {

private:

    ifstream infile;
    string line;
    string inputFileName;
    string outFileName;
    int serializationType;
    long numberOfTweets;

public:
    DataSerialization();

    DataSerialization(const string &inputFileName, const string &outFileName, int serializationType,
                      long numberOfTweets);
   virtual ~DataSerialization();

    void runTheDataSerialization();

};

template<class T>
void DataSerialization<T>::runTheDataSerialization() {

    // define a blocking queue for read raw tweets from file:
    ReaderWriterQueue<string> tweetQueue(1000);

    // start to read tweets from file and add it into a blocking lock free queue:
     bool readStatus=true;

    std::thread writer([&]() {
        while (readStatus) {
        infile.open(inputFileName);
        int l = 0;
        while (getline(infile, line) && readStatus) {
            while (!tweetQueue.try_enqueue(line) && readStatus);
        }
        infile.close();
        infile.clear();
        }
    });

    // read raw tweet from queue and then do serialization:
    string line;

    // Define file handler for each serialization type:
    FileHandler<T> *fileHandler=new FileHandler<T>(outFileName,serializationType);
    fileHandler->prepareToWrite();
    DataReader dataReader;

    for (int i = 0; i < this->numberOfTweets; ++i) {
        // Fully-blocking:
        while (!tweetQueue.try_dequeue (line))
            ;
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
    readStatus= false;
    writer.join();

    fileHandler->appendObjectToFileFlush();
    delete  fileHandler;

}

template<class T>
DataSerialization<T>::DataSerialization() {}

template<class T>
DataSerialization<T>::~DataSerialization() {

}

template<class T>
DataSerialization<T>::DataSerialization(const string &inputFileName, const string &outFileName, int serializationType,
                                        long numberOfTweets):inputFileName(inputFileName), outFileName(outFileName),
                                                             serializationType(serializationType),
                                                             numberOfTweets(numberOfTweets) {}


#endif //TWITTER_DATASERIALIZATION_H
