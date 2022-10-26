#include "DataReadNetworkIO.h"
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
            DataReadNetworkIO<TweetStatus> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case INPLACE: {
            DataReadNetworkIO<TweetStatusIP> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case PROTOBUF: {
            DataReadNetworkIO<TweetStatusProto> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        case FLATBUF: {
            DataReadNetworkIO<TweetStatusFlatBuffers> dataReadNetwork(config,inDataPath, outDataPath,method, plan);
            dataReadNetwork.runDataReader();
            break;
        }
        default: {
            throw std::runtime_error("The selected serialization method is not support!! ");
        }
    }

    return 0;
}