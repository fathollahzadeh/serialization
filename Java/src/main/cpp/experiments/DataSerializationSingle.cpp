#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    int nrow = atoi(argv[3]);

    ObjectReader *reader = new ObjectReader(inDataPath,"HandCoded");
    ObjectWriter *writer = new ObjectWriter(method, nrow, PAGESIZE);

    int size = BATCHSIZE;
    for (int i=0; i<nrow;){
        TweetStatus ** tweets = new TweetStatus*[nrow];
        int rdSize =  reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize ; j++) {
            tweets[j]->hasBsonDoc = false;
            writer->serializeObject(tweets[j]);
            delete tweets[j];
        }
        i += rdSize;
        size = min(nrow - i, BATCHSIZE);
        delete[] tweets;
    }
    writer->flush();
    delete reader;
    delete writer;
    return 0;


}



