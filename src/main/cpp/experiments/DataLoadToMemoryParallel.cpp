#include <iostream>
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include <thread>
#include "math.h"

using namespace std;

void DeSerializeTask(string inDataPath, int beginPos, int endPos) {
    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    int size = BATCHSIZE;
    for (int i = beginPos; i < endPos;) {
        TweetStatus **tweets = new TweetStatus *[size];
        int rdSize = reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize; j++)
            delete tweets[j];
        i += rdSize;
        size = min(endPos - i, BATCHSIZE);
        delete[] tweets;
    }
    delete reader;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    int nrow = atoi(argv[2]);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        pool.push_back(std::thread(DeSerializeTask, inDataPath, i * blklen, min((i + 1) * blklen, nrow)));
    }
    for (auto &th: pool) {
        th.join();
    }

    return 0;
}
