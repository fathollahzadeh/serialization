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
//#include "ComplexObject1FBS.h"
//#include "ComplexObject2FBS.h"
//#include "ComplexObject3FBS.h"
//#include "ComplexObject4FBS.h"
//#include "ComplexObject5FBS.h"
//#include "ComplexObject6FBS.h"
//#include "ComplexObject7FBS.h"
//#include "ComplexObject8FBS.h"
//#include "ComplexObject9FBS.h"
//#include "ComplexObject10FBS.h"
//#include "ComplexObject11FBS.h"
//#include "ComplexObject12FBS.h"
#include "ComplexObject13FBS.h"
//#include "ComplexObject14FBS.h"
//#include "ComplexObject15FBS.h"
//#include "SimpleObjectFBS.h"
#include <random>
#include <chrono>

using namespace complexobjectflatbuffers;

static std::string randString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0";

static flatbuffers::Offset<SimpleObjectFBS> genSimpleObject(flatbuffers::FlatBufferBuilder &builder) {

    auto var_stringBuilder = builder.CreateString(randString);
    SimpleObjectFBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject15FBS> genComplexObject15(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genSimpleObject(builder);
    ComplexObject15FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject14FBS> genComplexObject14(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject15(builder);
    ComplexObject14FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject13FBS> genComplexObject13(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject14(builder);
    ComplexObject13FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject44(complexObject);
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
    auto arc = genComplexObject15(builder);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genComplexObject13(tmpBuilder);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();

        ComplexObject13FBST * complexObject = new ComplexObject13FBST();
        GetComplexObject13FBS(buffer)->UnPackTo(complexObject);
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
    cout << "FlatBuffer ComplexObjectL4 avg serialization=" << avg << "  avg deserialize=" << avgd << "   buffer size="<<bufferSize<< endl;

    return 0;
}





