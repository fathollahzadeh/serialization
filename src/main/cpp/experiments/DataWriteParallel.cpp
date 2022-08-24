#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include <math.h>
#include <sys/stat.h>

using namespace std;

void WriteTask(ObjectReader *reader, string method, string fname, int beginPos, int endPos) {
    ObjectWriter *writer = new ObjectWriter( fname, method, endPos - beginPos +1);
    int size = BATCHSIZE;
    for (int i = beginPos; i < endPos;) {
        TweetStatus **tweets = new TweetStatus *[size];
        int rdSize = reader->readObjects(i, size, tweets);
        for (int j = 0; j < rdSize; j++) {
            writer->writeObjectToFile(tweets[j]);
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
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);
    string method = argv[4];

    vector<thread> pool;
    int start = 0;
    int end = outDataPath.find(".");
    outDataPath = outDataPath.substr(start, end - start);

    struct stat s;
    if( stat(outDataPath.c_str(),&s) == 0 ){
        if( s.st_mode & !S_IFDIR ){
            mkdir(outDataPath.c_str(), 0777);
        }
    }
    else{
        mkdir(outDataPath.c_str(), 0777);
    }

    outDataPath = outDataPath + "/" + method;
    if( stat(outDataPath.c_str(),&s) == 0 ){
        if( s.st_mode & !S_IFDIR ){
            mkdir(outDataPath.c_str(), 0777);
        }
    }
    else{
        mkdir(outDataPath.c_str(), 0777);
    }

    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        ObjectReader *reader = new ObjectReader(inDataPath,"HandCoded");
        pool.push_back(std::thread(WriteTask, reader, method, outDataPath + "/" + to_string(i) ,i * blklen, min((i + 1) * blklen, nrow)));
    }

    for (auto &th: pool) {
        th.join();
    }
}



