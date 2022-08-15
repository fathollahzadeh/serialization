#include <iostream>
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string seqRand = argv[2];
    string method = argv[3];
    int nrow = atoi(argv[4]);

    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    int size = BATCHSIZE;
    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        for (int i = 0; i < nrow;) {
            TweetStatus **tweets = new TweetStatus *[size];
            int rdSize = reader->readObjects(i, size, tweets);
            i += rdSize;
            size = min(nrow - i, BATCHSIZE);
            delete[] tweets;
        }
    } else{
        //TODO: parallel load to memory
    }

    delete reader;
    return 0;
}
