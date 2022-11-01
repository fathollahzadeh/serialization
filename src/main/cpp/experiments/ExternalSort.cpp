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
#include "Const.h"
#include "ExternalSort.h"

using namespace std;

int main(int argc, char *argv[]) {

    string inDataPath = argv[1];
    string outDataPath = argv[2];
    string method = argv[3];
    int chunkSize = atoi(argv[4]);

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

    //if serialization type is Handcoded or Boost:
    if (methodID == HANDCODED || methodID == BOOST || methodID == BSON) {
        ExternalSort<TweetStatus> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is InPlace:
    else if (methodID == INPLACE) {
        ExternalSort<TweetStatusIP> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is Proto:
    else if (methodID == PROTOBUF) {
        ExternalSort<TweetStatusProto> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }
        //if serialization type is Proto:
    else if (methodID == FLATBUF) {
        ExternalSort<TweetStatusFlatBuffers> externalSort(inDataPath, outDataPath, method, chunkSize);
        externalSort.runExternalSort();
    }

    return 0;
}



