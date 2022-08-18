#ifndef CPP_OBJECTREADER_H
#define CPP_OBJECTREADER_H

#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
#include "TweetStatus.h"
#include <TweetStatusIP.h>
#include <TweetStatusProto.h>
#include <TweetStatusFlatBuffers.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Const.h"
#include "RootData.h"
#include "Object.h"

using namespace std;

class ObjectReader {
protected:
    long currentPageNumber;
    int currentOffset;
    int row;
    int rlen;
    int method;
    char *pageBuffer;
    int *pageIndex;
    int *objectIndex;
    map<int, int> objectInEachPage;
    ifstream inStreamRegularFile;
private:
    RootData rootData;

    void  readIndexesFromFile(const string & fname);

    char * readPageFromFile(int id);

public:
    ObjectReader(const string & fname, const string &method);

    ObjectReader(const string &method);

    int readObjects(int i, int n, TweetStatus ** objectList);
    TweetStatus * readObject(int i);

    int readObjects(int i, int n, TweetStatusIP ** objectList);
    TweetStatusIP * readObjectIP(int i);

    int readObjects(int i, int n, TweetStatusProto ** objectList);
    TweetStatusProto * readObjectProto(int i);

    int readObjects(int i, int n, TweetStatusFlatBuffers ** objectList);
    TweetStatusFlatBuffers * readObjectFlatBuffers(int i);

    void readIO(long i, int n);
    void readIO(long i);

    int getRlen();

    int getMethod() const;
    //HashMap<Integer, Integer> getObjectInEachPage()
};
#endif //CPP_OBJECTREADER_H