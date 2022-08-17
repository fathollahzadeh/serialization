#include <iostream>
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include "math.h"

using namespace std;

void ReadIOTask(ObjectReader *reader, int beginPos, int endPos) {
    reader->readIO(beginPos, endPos - beginPos + 1);
    delete reader;
}

void ReadIOTaskRandom(ObjectReader *reader, int *randomIDs, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++)
        reader->readIO(randomIDs[i]);
    delete reader;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    string seqRand = argv[3];
    int nrow = atoi(argv[4]);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);

    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
            ObjectReader *reader = new ObjectReader(inDataPath, method);
            pool.push_back(std::thread(ReadIOTask, reader, i * blklen, min((i + 1) * blklen, nrow)));
        }

        for (auto &th: pool) {
            th.join();
        }
    } else {
        string randomDataPath = argv[5];
        ifstream infile;
        infile.open(randomDataPath);
        if (!infile.is_open()) {
            throw runtime_error("cannot find random list file!!.");
        }
        int *randomIDs = new int[nrow];
        string line;
        int index = 0;
        while (getline(infile, line)) {
            int id = atoi(line.c_str());
            randomIDs[index++] = id;
        }

        for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
            ObjectReader *reader = new ObjectReader(inDataPath, method);
            pool.push_back(std::thread(ReadIOTaskRandom, reader, randomIDs, i * blklen, min((i + 1) * blklen, nrow)));
        }

        for (auto &th: pool) {
            th.join();
        }

        delete[] randomIDs;
    }
}