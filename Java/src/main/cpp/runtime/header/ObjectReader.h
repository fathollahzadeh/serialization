#ifndef C___OBJECTREADER_H
#define C___OBJECTREADER_H

#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
//#include "RootData.h"
//#include "TweetStatus.h"
//#include <Object.h>
//#include <TweetStatusIP.h>
//#include <TweetStatusProto.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//#include <TweetStatusFlatBuffers.h>

using namespace std;

class ObjectReader {
protected:
    long currentPageNumber;
    int currentOffset;
    int row;
    int rlen;
    string method;
    char *pageBuffer;
    int *pageIndex;
    int *objectIndex;
    int *objectLength;
    map<int, int> objectInEachPage;
    //FileChannel inStreamRegularFile;
    //ByteBuffer bbPageBuffer;
    //Kryo kryo;
private:
    void readIndexesFromFile(string fname);

public:
    ObjectReader(const string & fname, const string &method);

    ObjectReader(const string &method);

    //RootData[] readObjects(long i, int n)
    //long readObjects(long i, int n, RootData[] rd)
    //long readObjects(long i, int n, ArrayList<RootData> rd)
    //void readIO(long i, int n)
    //protected void readPage(long id)
    //RootData readObjectWithSerialization(TweetStatus myData, byte[] buffData)
    //int getRlen()
    //HashMap<Integer, Integer> getObjectInEachPage()
};
#endif //C___OBJECTREADER_H
