#include "DataReadNetworkNetworkIO.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    string method = argv[3];
    string config = argv[4];
    string plan = argv[5];

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

    switch (methodID) {
        case HANDCODED:
        case BOOST:
        case BSON: {
            DataReadNetworkNetworkIO<TweetStatus> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case INPLACE: {
            DataReadNetworkNetworkIO<TweetStatusIP> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case PROTOBUF: {
            DataReadNetworkNetworkIO<TweetStatusProto> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case FLATBUF: {
            DataReadNetworkNetworkIO<TweetStatusFlatBuffers> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        default: {
            throw std::runtime_error("The selected serialization method is not support!! ");
        }
    }

    return 0;
}