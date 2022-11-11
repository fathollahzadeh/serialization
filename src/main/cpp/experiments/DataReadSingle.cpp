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

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string method = argv[2];
    string seqRand = argv[3];
    int nrow = atoi(argv[4]);

    ObjectReader *reader = new ObjectReader(inDataPath, method);
    if (strcasecmp(seqRand.c_str(), "sequential") == 0) {
        switch (reader->getMethod()) {
            case HANDCODED:
            case BOOST:
            case BSON: {
                TweetStatus **tweets = new TweetStatus *[nrow];
                int listSize = reader->readObjects(0, nrow, tweets);
                for (int i = 0; i < listSize; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
            case INPLACE: {
                TweetStatusIP **tweets = new TweetStatusIP *[nrow];
                int listSize = reader->readObjects(0, nrow, tweets);
                for (int i = 0; i < listSize; ++i) {
                    char *tbuffer = (char *)  tweets[i];
                    delete[] tbuffer;
                }
                delete[] tweets;
                break;
            }
            case PROTOBUF: {
                TweetStatusProto **tweets = new TweetStatusProto *[nrow];
                int listSize = reader->readObjects(0, nrow, tweets);
                for (int i = 0; i < listSize; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
            case FLATBUF: {
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[nrow];
                int listSize = reader->readObjects(0, nrow, tweets);
                for (int i = 0; i < listSize; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
        }
    } else {
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
            randomIDs[index++] = atoi(line.c_str());
        }
        index = 0;
        switch (reader->getMethod()) {
            case HANDCODED:
            case BOOST:
            case BSON: {
                TweetStatus **tweets = new TweetStatus *[nrow];
                for (int i = 0; i< nrow; i++)
                    tweets[index++] = reader->readObject(randomIDs[i]);

                for (int i = 0; i < nrow; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
            case INPLACE: {
                TweetStatusIP **tweets = new TweetStatusIP *[nrow];
                for (int i = 0; i< nrow; i++)
                    tweets[index++] = reader->readObjectIP(randomIDs[i]);
                for (int i = 0; i < nrow; ++i) {
                    char *tbuffer = (char *)  tweets[i];
                    delete[] tbuffer;
                }
                delete[] tweets;
                break;
            }
            case PROTOBUF: {
                TweetStatusProto **tweets = new TweetStatusProto *[nrow];
                for (int i = 0; i< nrow; i++)
                    tweets[index++] = reader->readObjectProto(randomIDs[i]);
                for (int i = 0; i < nrow; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
            case FLATBUF: {
                TweetStatusFlatBuffers **tweets = new TweetStatusFlatBuffers *[nrow];
                for (int i = 0; i< nrow; i++)
                    tweets[index++] = reader->readObjectFlatBuffers(randomIDs[i]);
                for (int i = 0; i < nrow; ++i) {
                    delete tweets[i];
                }
                delete[] tweets;
                break;
            }
        }
    }
    delete reader;
}



