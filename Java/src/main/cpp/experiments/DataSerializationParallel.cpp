#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include "math.h"

using namespace std;

void SerializeTask(ObjectReader *reader, string method, int beginPos, int endPos) {
    ObjectWriter *writer = new ObjectWriter(method, endPos - beginPos +1, PAGESIZE);
    int size = BATCHSIZE;
    for (int i = beginPos; i < endPos;) {
        TweetStatus **tweets = new TweetStatus *[size];
        int rdSize = reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize; j++) {
            writer->serializeObject(tweets[j]);
            delete tweets[j];
        }
        i += rdSize;
        size = min(endPos - i, BATCHSIZE);
        delete[] tweets;
    }
    delete reader;
    delete writer;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    int nrow = atoi(argv[3]);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        ObjectReader *reader = new ObjectReader(inDataPath,"HandCoded");
        pool.push_back(std::thread(SerializeTask, reader, method, i * blklen, min((i + 1) * blklen, nrow)));
    }

    for (auto &th: pool) {
        th.join();
    }
    return 0;
}



