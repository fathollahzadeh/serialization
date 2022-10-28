#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include <thread>
#include "math.h"

using namespace std;

void DeSerializeTask(char **buffer, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++) {
        TweetStatus *object = new TweetStatus();
        int objectSize = 0;
        object->deserializeHandcoded(buffer[i], objectSize);
        delete[] buffer[i];
        delete object;
    }
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    int nrow = atoi(argv[2]);

    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    char **buffer = new char*[nrow];
    reader->readBinaryObjects(buffer);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        pool.push_back(std::thread(DeSerializeTask, buffer, i * blklen, min((i + 1) * blklen, nrow)));
    }
    for (auto &th: pool) {
        th.join();
    }
    delete[] buffer;
    return 0;
}
