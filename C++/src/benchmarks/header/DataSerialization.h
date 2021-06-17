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
#include <LogFileHandler.h>

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
	bool taskset;
	LogFileHandler *logFileHandler;

public:
	DataSerialization();

	DataSerialization(string inputFileName, string outFileName, int serializationType, long numberOfTweets, int round,
					  bool taskset);

	virtual ~DataSerialization();

	void runTheDataSerialization();

};

template<class T>
void DataSerialization<T>::runTheDataSerialization() {

	// define a blocking queue for read raw tweets from file:
	ReaderWriterQueue <string> tweetQueue(1000);

	// start to read tweets from file and add it into a blocking lock free queue:
	bool readStatus = true;

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
	FileHandler <T> *fileHandler = new FileHandler<T>(outFileName, serializationType);
	fileHandler->prepareToWrite();
	DataReader dataReader;

	// start of time calculation

	double elapsedSeconds = 0;

	for (int i = 0; i < this->numberOfTweets; ++i) {
		// Fully-blocking:
		while (!tweetQueue.try_dequeue(line));
		Document d;
		//Parse read data:
		d.Parse(line.c_str());

		//Convert json data to the TweetStatus Object:
		TweetStatus *tweet = dataReader.generateTweetObject(d);

		auto tmpTime = chrono::steady_clock::now();

		//Serialize the TweetStatus object and then write to file:
		fileHandler->appendObjectToFile(tweet);

		elapsedSeconds += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

		//Free memory:
		delete tweet;
	}

	auto tmpTime = chrono::steady_clock::now();
	fileHandler->appendObjectToFileFlush();
	elapsedSeconds += chrono::duration<double>(chrono::steady_clock::now() - tmpTime).count();

	// add times to the log file
	this->logFileHandler->addLog(false, serializationType, true, "TweetStatus", fileHandler->getIoTime(),
								 elapsedSeconds, taskset);
	this->logFileHandler->flushLogFile();


	readStatus = false;
	writer.join();


	delete fileHandler;

}

template<class T>
DataSerialization<T>::DataSerialization() {}

template<class T>
DataSerialization<T>::~DataSerialization() {

}

template<class T>
DataSerialization<T>::DataSerialization(string inputFileName, string outFileName, int serializationType,
										long numberOfTweets, int round, bool taskset) {
	this->inputFileName = inputFileName;
	this->outFileName = outFileName;
	this->serializationType = serializationType;
	this->numberOfTweets = numberOfTweets;
	this->taskset = taskset;
	this->logFileHandler = new LogFileHandler(
			"bin/benchmark/writeobjects/result_cpp_writeobjects_" + to_string(numberOfTweets) + "_" + to_string(round) +
			".txt");
}


#endif //TWITTER_DATASERIALIZATION_H
