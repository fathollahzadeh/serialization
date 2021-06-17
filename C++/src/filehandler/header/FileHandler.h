#ifndef C_FILEHANDLER_H
#define C_FILEHANDLER_H

#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
#include "RootData.h"
#include "TweetStatus.h"
#include <Object.h>
#include <TweetStatusIP.h>
#include <TweetStatusProto.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <TweetStatusFlatBuffers.h>

using namespace std;

template<class T>
class FileHandler : public RootData {

private:

	string fileName;

	int pageSize;

	long currentPageNumber;

	int currentOffset;

	int countObject;

	char *pageBuffer;

	//total number of objects in serialized file:
	long totalOfObjects;

	//Output Stream: For Writing:
	ofstream outStreamRegularFile;

	//Output Stream: For Index Writing:
	ofstream outIndexFile;

	//Input Stream: For Reading:
	ifstream inStreamRegularFile;

	//Page index:
	vector<long> pageIndex;

	//Object index:
	vector<long> objectIndex;

	//Object in each page:
	map<long, long> objectInEachPage;

	//Write data index to the an index file:
	void writeIndexToFile(vector<long> indexMap);

	void readIndexesFromFile();

	char *readPageFromFile(long id);

	int serializationType;

	void appendInPlaceObjectToFile(TweetStatus *object);

	//benchmark times:
	double ioTime;
	double indexTime;

	//Network Experiments:
	long networkPageSize;

public:

	FileHandler();

	FileHandler(string fileName, int serializationType);

	void prepareToWrite();

	void prepareToRead();

	virtual ~FileHandler();

	void appendObjectToFile(TweetStatus *object);

	void appendObjectToFile(TweetStatusIP *object);

	void appendObjectToFile(TweetStatusProto *object);

	void appendObjectToFile(TweetStatusFlatBuffers *object);

	void appendObjectToFileFlush();

	void getObjectsFromFile(long i, long n, vector<T *> &objectList);

	// define a method for get network page count from RAM object list
	int getNextNetworkPage(vector<T *> &objectList, int startIndex, int numObjects, char *networkBuffer);

	int parseNetworkPage(vector<T *> &curObjectList, char *networkBuffer);

	//Number of network pages to be sent from disk:
	long getNetworkPageCount(int numObjects);

	//Simply reads the next network page from file:
	long getNextNetworkPage(char *networkBuffer);

	void getObjectsFromFileFlush();

	long getNumberOfObjects();

	map<long, long> getEachPageObjectCount();

	double getIoTime() const;

	void setNetworkPageSize(long networkPageSize);
};


#endif //C_FILEHANDLER_H
