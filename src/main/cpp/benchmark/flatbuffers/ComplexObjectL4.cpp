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
#include "ComplexObject1FBS.h"
#include "SimpleObjectFBS.h"
#include <chrono>

using namespace std;
using namespace complexobjectflatbuffers;

std::string randString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0";

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
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject12FBS> genComplexObject12(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject13(builder);
    ComplexObject12FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject11FBS> genComplexObject11(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject12(builder);
    ComplexObject11FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject10FBS> genComplexObject10(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject11(builder);
    ComplexObject10FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}
static flatbuffers::Offset<ComplexObject9FBS> genComplexObject9(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject10(builder);
    ComplexObject9FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject8FBS> genComplexObject8(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject9(builder);
    ComplexObject8FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject7FBS> genComplexObject7(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject8(builder);
    ComplexObject7FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject6FBS> genComplexObject6(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject7(builder);
    ComplexObject6FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject5FBS> genComplexObject5(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject6(builder);
    ComplexObject5FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject4FBS> genComplexObject4(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject5(builder);
    ComplexObject4FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject3FBS> genComplexObject3(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject4(builder);
    ComplexObject3FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject2FBS> genComplexObject2(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject3(builder);
    ComplexObject2FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static flatbuffers::Offset<ComplexObject1FBS> genComplexObject1(flatbuffers::FlatBufferBuilder &builder) {
    auto var_stringBuilder = builder.CreateString(randString);
    auto complexObject = genComplexObject2(builder);
    ComplexObject1FBSBuilder fbsBuilder(builder);
    fbsBuilder.add_var_string(var_stringBuilder);
    fbsBuilder.add_complexobject(complexObject);
    auto orc = fbsBuilder.Finish();
    return orc;
}

static string genRandomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

static void run1(){
    randString = genRandomString(1024);
    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 500000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    auto arc = genSimpleObject(builder);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genSimpleObject(tmpBuilder);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto * complexObject = new SimpleObjectFBST();
        GetSimpleObjectFBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        tmpBuilder.Clear();
        delete[] buffer;
    }

    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "FlatBuf,1," << avg << "," << avgd << ","<<bufferSize<< endl;
}

static void run2(){
    randString = genRandomString(512);
    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 500000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    auto arc = genComplexObject15(builder);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genComplexObject15(tmpBuilder);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto * complexObject = new ComplexObject15FBST();
        GetComplexObject15FBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        tmpBuilder.Clear();
        delete[] buffer;
    }

    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "FlatBuf,2," << avg << "," << avgd << ","<<bufferSize<< endl;
}

static void run4(){
    randString = genRandomString(256);
    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 500000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    auto arc = genComplexObject13(builder);
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
        auto * complexObject = new ComplexObject13FBST();
        GetComplexObject13FBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        tmpBuilder.Clear();
        delete[] buffer;
    }

    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "FlatBuf,4," << avg << "," << avgd << ","<<bufferSize<< endl;
}

static void run8(){
    randString = genRandomString(128);
    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 500000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    auto arc = genComplexObject9(builder);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genComplexObject9(tmpBuilder);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto * complexObject = new ComplexObject9FBST();
        GetComplexObject9FBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        tmpBuilder.Clear();
        delete[] buffer;
    }

    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "FlatBuf,8," << avg << "," << avgd << ","<<bufferSize<< endl;
}

static void run16(){
    randString = genRandomString(64);
    flatbuffers::FlatBufferBuilder builder(1024);
    int totalObjects = 500000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    auto arc = genComplexObject1(builder);
    builder.Finish(arc);
    bufferSize = builder.GetSize();

    for (int i = 0; i < totalObjects; ++i) {
        flatbuffers::FlatBufferBuilder tmpBuilder(bufferSize);
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto orc = genComplexObject1(tmpBuilder);
        uint8_t *bp;
        tmpBuilder.Finish(orc);
        bp = tmpBuilder.GetBufferPointer();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        memmove(buffer, (char *) bp, bufferSize);

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto * complexObject = new ComplexObject1FBST();
        GetComplexObject1FBS(buffer)->UnPackTo(complexObject);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        tmpBuilder.Clear();
        delete[] buffer;
    }

    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "FlatBuf,16," << avg << "," << avgd << ","<<bufferSize<< endl;
}

int main(int argc, char *argv[]) {
    run1();
    run2();
    run4();
    run8();
    run16();
    return 0;
}





