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

#include "proto/SimpleObject.pb.h"
#include <random>
#include <chrono>

using namespace std;

static string genRandomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
    //return "123456789012345678901234567890123456789";
}

static proto::SimpleObject *genSimpleObject() {
    proto::SimpleObject *cObject = new proto::SimpleObject();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);
    cObject->set_var_int325(50000);
    cObject->set_var_int326(50000);
    cObject->set_var_int327(50000);
    cObject->set_var_int328(50000);
    cObject->set_var_int329(50000);
    cObject->set_var_int3210(50000);
    cObject->set_var_int3211(50000);
    cObject->set_var_int3212(50000);
    cObject->set_var_int3213(50000);
    cObject->set_var_int3214(50000);
    cObject->set_var_int3215(50000);
    cObject->set_var_int3216(10000);

    cObject->set_var_int641(10000000);
    cObject->set_var_int642(10000000);
    cObject->set_var_int643(10000000);
    cObject->set_var_int644(10000000);
    cObject->set_var_int645(10000000);
    cObject->set_var_int646(10000000);
    cObject->set_var_int647(10000000);
    cObject->set_var_int648(10000000);
    cObject->set_var_int649(10000000);
    cObject->set_var_int6410(10000000);
    cObject->set_var_int6411(10000000);
    cObject->set_var_int6412(10000000);
    cObject->set_var_int6413(10000000);
    cObject->set_var_int6414(10000000);
    cObject->set_var_int6415(10000000);
    cObject->set_var_int6416(10000000);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);
    cObject->set_var_float5(1.1);
    cObject->set_var_float6(1.1);
    cObject->set_var_float7(1.1);
    cObject->set_var_float8(1.1);
    cObject->set_var_float9(1.1);
    cObject->set_var_float10(1.1);
    cObject->set_var_float11(1.1);
    cObject->set_var_float12(1.1);
    cObject->set_var_float13(1.1);
    cObject->set_var_float14(1.1);
    cObject->set_var_float15(1.1);
    cObject->set_var_float16(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);
    cObject->set_var_double5(2.2);
    cObject->set_var_double6(2.2);
    cObject->set_var_double7(2.2);
    cObject->set_var_double8(2.2);
    cObject->set_var_double9(2.2);
    cObject->set_var_double10(2.2);
    cObject->set_var_double11(2.2);
    cObject->set_var_double12(2.2);
    cObject->set_var_double13(2.2);
    cObject->set_var_double14(2.2);
    cObject->set_var_double15(2.2);
    cObject->set_var_double16(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);
    cObject->set_var_bool5(true);
    cObject->set_var_bool6(true);
    cObject->set_var_bool7(true);
    cObject->set_var_bool8(true);
    cObject->set_var_bool9(true);
    cObject->set_var_bool10(true);
    cObject->set_var_bool11(true);
    cObject->set_var_bool12(true);
    cObject->set_var_bool13(true);
    cObject->set_var_bool14(true);
    cObject->set_var_bool15(true);
    cObject->set_var_bool16(true);

    cObject->set_var_string1(genRandomString(32));
    cObject->set_var_string2(genRandomString(32));
    cObject->set_var_string3(genRandomString(32));
    cObject->set_var_string4(genRandomString(32));
    cObject->set_var_string5(genRandomString(32));
    cObject->set_var_string6(genRandomString(32));
    cObject->set_var_string7(genRandomString(32));
    cObject->set_var_string8(genRandomString(32));
    cObject->set_var_string9(genRandomString(32));
    cObject->set_var_string10(genRandomString(32));
    cObject->set_var_string11(genRandomString(32));
    cObject->set_var_string12(genRandomString(32));
    cObject->set_var_string13(genRandomString(32));
    cObject->set_var_string14(genRandomString(32));
    cObject->set_var_string15(genRandomString(32));
    cObject->set_var_string16(genRandomString(32));

    return cObject;
}


int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    srand((unsigned) time(NULL));

    int count = 0;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;

    for (int i = 0; i < totalObjects; ++i) {
        proto::SimpleObject *simpleObject = genSimpleObject();
        bufferSize = simpleObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        simpleObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::SimpleObject *dSimpleObject = new proto::SimpleObject();
        dSimpleObject->ParseFromArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        count++;

        delete simpleObject;
        delete dSimpleObject;
        delete[] buffer;
    }

    double avg = sum_serialization / count;
    double avgd = sum_deserialization / count;
    cout << "SimpleObject avg serialization=" << avg << "  avg deserialize=" << avgd<< "   buffer size="<<bufferSize << endl;

    return 0;
}





