#include <iostream>
#include "Const.h"
#include "ExternalSort.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    string method = argv[3];
    int chunkSize = atoi(argv[4]);

    int methodID = -1;
    if (strcasecmp(method.c_str(), "HandCoded") == 0) {
        methodID = HANDCODED;
    } else if (strcasecmp(method.c_str(), "InPlace") == 0) {
        methodID = INPLACE;
    } else if (strcasecmp(method.c_str(), "Boost") == 0) {
        methodID = BOOST;
    } else if (strcasecmp(method.c_str(), "ProtoBuf") == 0) {
        methodID = PROTOBUF;
    } else if (strcasecmp(method.c_str(), "Bson") == 0) {
        methodID = BSON;
    } else if (strcasecmp(method.c_str(), "FlatBuf") == 0) {
        methodID = FLATBUF;
    }

    //const string &inDataPath, const string &outDataPath, const string &method, int chunkSize
    //if serialization type is Handcoded or Boost:
    if (methodID == HANDCODED || methodID == BOOST || methodID == BSON) {
        ExternalSort<TweetStatus> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is InPlace:
    else if (methodID == INPLACE) {
        ExternalSort<TweetStatusIP> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is Proto:
    else if (methodID == PROTOBUF) {
        ExternalSort<TweetStatusProto> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is Proto:
    else if (methodID == FLATBUF) {
        ExternalSort<TweetStatusFlatBuffers> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }

    return 0;
}



