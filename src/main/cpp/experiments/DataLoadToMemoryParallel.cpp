/*
* Copyright 2023 Saeed Fathollahzadeh. All rights reserved.
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
    delete reader;
    return 0;
}
