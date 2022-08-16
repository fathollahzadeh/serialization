#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    string seqRand = argv[3];
    int nrow = atoi(argv[4]);

    ObjectReader *reader = new ObjectReader(inDataPath,method);
    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        switch (reader->getMethod()) {
            case HANDCODED:
            case BOOST:
            case BSON:{
                TweetStatus **tweets = new TweetStatus *[reader->getRlen()];
                reader->readObjects(0, nrow, tweets);
                break;
            }
            case INPLACE:{
                TweetStatusIP **tweets = new TweetStatusIP *[reader->getRlen()];
                reader->readObjects(0, nrow, tweets);
                break;
            }
            case PROTOBUF:{
                TweetStatusProto **tweets = new TweetStatusProto *[reader->getRlen()];
                reader->readObjects(0, nrow, tweets);
                break;
            }
            case FLATBUF:{
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[reader->getRlen()];
                reader->readObjects(0, nrow, tweets);
                break;
            }
        }
    }
    else{
        string randomDataPath = argv[5];
        ifstream infile;
        infile.open(randomDataPath);
        if (!infile.is_open()) {
            throw runtime_error("cannot find random list file!!.");
        }

        string line;
        int randomIDs[nrow];
        int index = 0;
        while (getline(infile, line)) {
            randomIDs[index++] = atol(line.c_str());
        }

        switch (reader->getMethod()) {
            case HANDCODED:
            case BOOST:
            case BSON:{
                TweetStatus **tweets = new TweetStatus *[reader->getRlen()];
                int index = 0;
                for (int i: randomIDs )
                    tweets[index++] = reader->readObject(i);

                break;
            }
            case INPLACE:{
                TweetStatusIP **tweets = new TweetStatusIP *[reader->getRlen()];
                int index = 0;
                for (int i: randomIDs )
                    tweets[index++] = reader->readObjectIP(i);
                break;
            }
            case PROTOBUF:{
                TweetStatusProto **tweets = new TweetStatusProto *[reader->getRlen()];
                int index = 0;
                for (int i: randomIDs )
                    tweets[index++] = reader->readObjectProto(i);
                break;
            }
            case FLATBUF:{
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[reader->getRlen()];
                int index = 0;
                for (int i: randomIDs )
                    tweets[index++] = reader->readObjectFlatBuffers(i);
                break;
            }
        }
    }
}



