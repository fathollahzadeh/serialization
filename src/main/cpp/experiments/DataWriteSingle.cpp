#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);
    string method = argv[4];

    ObjectReader *reader = new ObjectReader(inDataPath,"HandCoded");
    ObjectWriter *writer = new ObjectWriter(outDataPath,method, nrow);

    int size = BATCHSIZE;
    for (int i=0; i<nrow;){
        TweetStatus ** tweets = new TweetStatus*[size];
        int rdSize =  reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize ; j++) {
            writer->writeObjectToFile(tweets[j]);
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



