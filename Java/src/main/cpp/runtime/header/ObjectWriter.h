#ifndef CPP_OBJECTWRITER_H
#define CPP_OBJECTWRITER_H

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


#include "Const.h"
#include "RootData.h"
#include "Object.h"

using namespace std;

class ObjectWriter {
protected:
    ofstream outStreamRegularFile;
    ofstream outIndexFile;
    long currentPageNumber;
    int currentOffset;
    int row;
    string method;
    char *pageBuffer;
    int rlen;
    int *pageIndex;
    int *objectIndex;
    int *objectLength;

private:
public:
    virtual ~ObjectWriter();

    ObjectWriter(const string &fname, const string &method, int rlen);

    ObjectWriter(const string &method, int rlen, int pageSize);

};


#endif //CPP_OBJECTWRITER_H
