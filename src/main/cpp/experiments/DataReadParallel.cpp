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
#include "ObjectReader.h"
#include "Const.h"
#include "DataReader.h"
#include "math.h"

using namespace std;

void ReadTask(ObjectReader *reader, TweetStatus **tweets, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; ++i)
        tweets[i] = reader->readObject(i);
    delete reader;
}

void ReadTaskIP(ObjectReader *reader, TweetStatusIP **tweets, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; ++i)
        tweets[i] = reader->readObjectIP(i);
    delete reader;
}

void ReadTaskProto(ObjectReader *reader, TweetStatusProto **tweets, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; ++i)
        tweets[i] = reader->readObjectProto(i);
    delete reader;
}

void ReadTaskFlatBuffers(ObjectReader *reader, TweetStatusFlatBuffers **tweets, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; ++i)
        tweets[i] = reader->readObjectFlatBuffers(i);
    delete reader;
}

void ReadTaskRandom(ObjectReader *reader, TweetStatus **tweets, int *randomIDs, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++)
        tweets[i] = reader->readObject(randomIDs[i]);
    delete reader;
}

void ReadTaskRandomIP(ObjectReader *reader, TweetStatusIP **tweets, int *randomIDs, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++)
        tweets[i] = reader->readObjectIP(randomIDs[i]);
    delete reader;
}

void ReadTaskRandomProto(ObjectReader *reader, TweetStatusProto **tweets, int *randomIDs, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++)
        tweets[i] = reader->readObjectProto(randomIDs[i]);
    delete reader;
}

void ReadTaskRandomFlatBuffers(ObjectReader *reader, TweetStatusFlatBuffers **tweets, int *randomIDs, int beginPos, int endPos) {
    for (int i = beginPos; i < endPos; i++)
        tweets[i] = reader->readObjectFlatBuffers(randomIDs[i]);
    delete reader;
}

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    string seqRand = argv[3];
    int nrow = atoi(argv[4]);
    int methodID = -1;
    if (strcasecmp(method.c_str(), "HandCoded") == 0) {
        methodID = HANDCODED;
    } else if (strcasecmp(method.c_str(), "InPlace") == 0) {
        methodID = INPLACE;
    } else if (strcasecmp(method.c_str(), "Boost") == 0) {
        methodID = BOOST;
    } else if (strcasecmp(method.c_str(), "ProtoBuf") == 0) {
        methodID = PROTOBUF;
    } else if (strcasecmp(method.c_str(), "Bson") == 0) {
        methodID = BSON;
    } else if (strcasecmp(method.c_str(), "FlatBuf") == 0) {
        methodID = FLATBUF;
    }

    vector<thread> pool;
    int blklen = (int) ceil((double) nrow / NUM_THREADS);

    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        switch (methodID) {
            case HANDCODED:
            case BOOST:
            case BSON: {
                TweetStatus **tweets = new TweetStatus *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTask, reader, tweets, i * blklen, min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case INPLACE: {
                TweetStatusIP **tweets = new TweetStatusIP *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskIP, reader, tweets, i * blklen, min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case PROTOBUF: {
                TweetStatusProto **tweets = new TweetStatusProto *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskProto, reader, tweets, i * blklen, min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case FLATBUF: {
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(
                            std::thread(ReadTaskFlatBuffers, reader, tweets, i * blklen, min((i + 1) * blklen, nrow)));
                }
                break;
            }
        }
    }
    else {
        string randomDataPath = argv[5];
        ifstream infile;
        infile.open(randomDataPath);
        if (!infile.is_open()) {
            throw runtime_error("cannot find random list file!!.");
        }

        string line;
        int *randomIDs = new int[nrow];
        int index = 0;
        while (getline(infile, line)) {
            randomIDs[index++] = atol(line.c_str());
        }

        switch (methodID) {
            case HANDCODED:
            case BOOST:
            case BSON: {
                TweetStatus **tweets = new TweetStatus *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskRandom, reader, tweets, randomIDs, i * blklen,
                                               min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case INPLACE: {
                TweetStatusIP **tweets = new TweetStatusIP *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskRandomIP, reader, tweets, randomIDs, i * blklen,
                                               min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case PROTOBUF: {
                TweetStatusProto **tweets = new TweetStatusProto *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskRandomProto, reader, tweets, randomIDs, i * blklen,
                                               min((i + 1) * blklen, nrow)));
                }
                break;
            }
            case FLATBUF: {
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[nrow];
                for (int i = 0; i < NUM_THREADS & i * blklen < nrow; i++) {
                    ObjectReader *reader = new ObjectReader(inDataPath, method);
                    pool.push_back(std::thread(ReadTaskRandomFlatBuffers, reader, tweets, randomIDs, i * blklen,
                                               min((i + 1) * blklen, nrow)));
                }
                break;
            }
        }
    }

    for (auto &th: pool) {
        th.join();
    }
}



