#include <iostream>
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string seqRand = argv[2];
    int nrow = atoi(argv[3]);

    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    int size = BATCHSIZE;
    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        for (int i = 0; i < nrow;) {
            TweetStatus **tweets = new TweetStatus *[size];
            int rdSize = reader->readObjects(i, size, tweets);
            for (int j = 0; j < rdSize; j++) {
                delete tweets[j];
            }
            i += rdSize;
            size = min(nrow - i, BATCHSIZE);
            delete[] tweets;
        }
    }
//    else {
//        string randomDataPath = argv[4];
//        ifstream infile;
//        infile.open(randomDataPath);
//        if (!infile.is_open()) {
//            throw runtime_error("cannot find random list file!!.");
//        }
//
//        string line;
//        int randomIDs[nrow];
//        int index = 0;
//        while (getline(infile, line)) {
//            randomIDs[index++] = atol(line.c_str());
//        }
//
//        switch (reader->getMethod()) {
//            case HANDCODED:
//            case BOOST:
//            case BSON: {
//                TweetStatus **tweets = new TweetStatus *[reader->getRlen()];
//                int index = 0;
//                for (int i: randomIDs) {
//                    tweets[index] = reader->readObject(i);
//                    delete tweets[index++];
//                }
//                delete[] tweets;
//                break;
//            }
//            case INPLACE: {
//                TweetStatusIP **tweets = new TweetStatusIP *[reader->getRlen()];
//                int index = 0;
//                for (int i: randomIDs) {
//                    tweets[index] = reader->readObjectIP(i);
//                    delete tweets[index++];
//                }
//                delete[] tweets;
//                break;
//            }
//            case PROTOBUF: {
//                TweetStatusProto **tweets = new TweetStatusProto *[reader->getRlen()];
//                int index = 0;
//                for (int i: randomIDs) {
//                    tweets[index] = reader->readObjectProto(i);
//                    delete tweets[index++];
//                }
//                delete[] tweets;
//                break;
//            }
//            case FLATBUF: {
//                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[reader->getRlen()];
//                int index = 0;
//                for (int i: randomIDs) {
//                    tweets[index] = reader->readObjectFlatBuffers(i);
//                    delete tweets[index++];
//                }
//                delete[] tweets;
//                break;
//            }
//        }
//    }

    delete reader;
    return 0;
}
