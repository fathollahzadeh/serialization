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
#include "SimpleObjectFBS.h"
#include <random>
#include <chrono>

using namespace std;
using namespace complexobjectflatbuffers;

static string genRandomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

static flatbuffers::Offset<SimpleObjectFBS> genSimpleObject(flatbuffers::FlatBufferBuilder &builder, std::string strValue) {

    auto var_stringBuilder = builder.CreateString(strValue);
    SimpleObjectFBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    auto orc = fbsBuilder.Finish();
    return orc;
}


int main(int argc, char *argv[]) {

    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 10000;
    int count = 0;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;
    std::string varStr = genRandomString(1024);
    auto arc = genSimpleObject(builder, varStr);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genSimpleObject(tmpBuilder, varStr);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        SimpleObjectFBST * complexObject = new SimpleObjectFBST();
        GetSimpleObjectFBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        count++;
        tmpBuilder.Clear();
       // delete complexObject;
        delete[] buffer;
    }

    double avg = sum_serialization / count;
    double avgd = sum_deserialization / count;
    cout << "FlatBuffer SimpleObject avg serialization=" << avg << "  avg deserialize=" << avgd << "   buffer size="<<bufferSize<< endl;

    return 0;
}





