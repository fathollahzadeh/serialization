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
            for (int j = 0; j < rdSize ; j++) {
                delete tweets[j];
            }
            i += rdSize;
            size = min(nrow - i, BATCHSIZE);
            delete[] tweets;
        }
    } else{
        //TODO: Random load to memory
        string randomDataPath = argv[4];
    }

    delete reader;
    return 0;
}
