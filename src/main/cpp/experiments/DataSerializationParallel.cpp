#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include "math.h"

using namespace std;

void SerializeTask(string method, char **buffer, int beginPos, int endPos) {
    ObjectWriter *writer = new ObjectWriter(method, endPos - beginPos + 1, PAGESIZE);
    for (int i = beginPos; i < endPos; i++) {
        TweetStatus *object = new TweetStatus();
        int objectSize = 0;
        object->deserializeHandcoded(buffer[i], objectSize);
        writer->serializeObject(object);
        delete[] buffer[i];
        delete object;
    }
    delete writer;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    int nrow = atoi(argv[3]);

    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    char **buffer = new char*[nrow];
    reader->readBinaryObjects(buffer);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        pool.push_back(std::thread(SerializeTask,method,  buffer, i * blklen, min((i + 1) * blklen, nrow)));
    }
    for (auto &th: pool) {
        th.join();
    }
    delete[] buffer;
    delete reader;
    return 0;
}