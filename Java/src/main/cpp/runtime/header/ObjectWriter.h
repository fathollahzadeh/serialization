#ifndef CPP_OBJECTWRITER_H
#define CPP_OBJECTWRITER_H

#include <iostream>
#include <map>
#include <cstring>
#include <fstream>
#include "thread"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <TweetStatus.h>
#include <TweetStatusIP.h>
#include <TweetStatusProto.h>
#include <TweetStatusFlatBuffers.h>


#include "Const.h"
#include "RootData.h"
#include "Object.h"

using namespace std;

class ObjectWriter {
protected:
    ofstream outStreamRegularFile;
    ofstream outIndexFile;
    int currentPageNumber;
    int currentOffset;
    int row;
    int method;
    char *pageBuffer;
    int rlen;
    int *pageIndex;
    int *objectIndex;


private:
    RootData rootData;

    void writeInPlaceObjectToFile(TweetStatus *object);

    void writeIndexToFile(int *indexVector);

public:
    virtual ~ObjectWriter();

    ObjectWriter(const string &fname, const string &method, int rlen);

    ObjectWriter(const string &method, int rlen, int pageSize);

    void serializeObject(TweetStatus *object);

    void writeObjectToFile(TweetStatus *object);

    void flush();
};


#endif //CPP_OBJECTWRITER_H