#ifndef CPP_OBJECTWRITER_H
#define CPP_OBJECTWRITER_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "thread"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <TweetStatus.h>
#include <TweetStatusIP.h>
#include <TweetStatusProto.h>
#include <TweetStatusFlatBuffers.h>
#include <netinet/in.h>
#include "ObjectReader.h"
#include "Client.h"
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

    void writeObjectToFile(TweetStatusIP *object);

    void writeObjectToFile(TweetStatusProto *object);

    void writeObjectToFile(TweetStatusFlatBuffers *object);

    void writeObjectToNetworkPage(TweetStatus *object, Client *client);

    void writeObjectToNetworkPage(TweetStatusIP *object, Client *client);

    void writeObjectToNetworkPage(TweetStatusProto *object, Client *client);

    void writeObjectToNetworkPage(TweetStatusFlatBuffers *object, Client *client);

    void writeToNetworkPage(char *page, Client *client);

    void writeNetworkPageToFile(char *page);

    void flushToNetwork(Client *client);

    void flush();

    void flushNetworkPageWriter();
};


#endif //CPP_OBJECTWRITER_H
