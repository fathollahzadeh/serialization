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
        object = object->deserializeHandcoded(buffer[i], objectSize);
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