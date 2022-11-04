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

#include "proto/ComplexObjectL2.pb.h"
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
}

static proto::ComplexObjectL23 *genComplexObjectL23() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL23 *cObject = new proto::ComplexObjectL23();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);

    cObject->set_var_string1(genRandomString(32));
    cObject->set_var_string2(genRandomString(32));
    cObject->set_var_string3(genRandomString(32));
    cObject->set_var_string4(genRandomString(31));
    return cObject;
}

static proto::ComplexObjectL22 *genComplexObjectL22() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL22 *cObject = new proto::ComplexObjectL22();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);

    cObject->set_var_string1(genRandomString(31));
    cObject->set_var_string2(genRandomString(31));
    cObject->set_var_string3(genRandomString(31));
    cObject->set_var_string4(genRandomString(30));
    cObject->set_allocated_complexobjectl23(genComplexObjectL23());

    return cObject;
}

static proto::ComplexObjectL21 *genComplexObjectL21() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL21 *cObject = new proto::ComplexObjectL21();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);

    cObject->set_var_string1(genRandomString(31));
    cObject->set_var_string2(genRandomString(31));
    cObject->set_var_string3(genRandomString(31));
    cObject->set_var_string4(genRandomString(30));
    cObject->set_allocated_complexobjectl22(genComplexObjectL22());

    return cObject;
}

static proto::ComplexObjectL2 *genComplexObjectL2() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL2 *cObject = new proto::ComplexObjectL2();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);

    cObject->set_var_string1(genRandomString(31));
    cObject->set_var_string2(genRandomString(31));
    cObject->set_var_string3(genRandomString(31));
    cObject->set_var_string4(genRandomString(30));
    cObject->set_allocated_complexobjectl21(genComplexObjectL21());

    return cObject;
}



int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    int count = 0;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL2 *cObject = genComplexObjectL2();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::ComplexObjectL2 *dcObject = new proto::ComplexObjectL2();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        count++;

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }

    double avg = sum_serialization / count;
    double avgd = sum_deserialization / count;
    cout << "ComplexObjectL2 avg serialization=" << avg << "  avg deserialize=" << avgd<< "   buffer size="<<bufferSize << endl;

    return 0;
}





