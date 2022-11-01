/*
* Copyright 2022 Saeed Fathollahzadeh. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <iostream>
#include "ObjectWriter.h"
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include <math.h>
#include <sys/stat.h>

using namespace std;

void WriteTask(string method, string fname, char **buffer, int beginPos, int endPos) {
    ObjectWriter *writer = new ObjectWriter( fname, method, endPos - beginPos +1);
    for (int i = beginPos; i < endPos; i++) {
        TweetStatus *object = new TweetStatus();
        int objectSize = 0;
        object->deserializeHandcoded(buffer[i], objectSize);
        writer->writeObjectToFile(object);
        delete[] buffer[i];
        delete object;
    }
    writer->flush();
    delete writer;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    int nrow = atoi(argv[3]);
    string method = argv[4];

    int start = 0;
    int end = outDataPath.find(".");
    outDataPath = outDataPath.substr(start, end - start);

    struct stat s;
    if (stat(outDataPath.c_str(), &s) == 0) {
        if (s.st_mode & !S_IFDIR) {
            mkdir(outDataPath.c_str(), 0777);
        }
    } else {
        mkdir(outDataPath.c_str(), 0777);
    }

    outDataPath = outDataPath + "/" + method;
    if (stat(outDataPath.c_str(), &s) == 0) {
        if (s.st_mode & !S_IFDIR) {
            mkdir(outDataPath.c_str(), 0777);
        }
    } else {
        mkdir(outDataPath.c_str(), 0777);
    }

    ObjectReader *reader = new ObjectReader(inDataPath, "HandCoded");
    char **buffer = new char*[nrow];
    reader->readBinaryObjects(buffer);

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);
    for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
        pool.push_back(std::thread(WriteTask,method, outDataPath + "/" + to_string(i), buffer, i * blklen, min((i + 1) * blklen, nrow)));
    }
    for (auto &th: pool) {
        th.join();
    }
    delete[] buffer;
    delete reader;
    return 0;
}


