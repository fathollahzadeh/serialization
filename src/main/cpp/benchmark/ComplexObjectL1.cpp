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

#include "proto/ComplexObjectL1.pb.h"
#include <random>
#include <chrono>

using namespace std;

static string genRandomString(int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}


static proto::ComplexObjectL11 *genComplexObjectL11() {
    proto::ComplexObjectL11 *cObject = new proto::ComplexObjectL11();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);
    cObject->set_var_int325(50000);
    cObject->set_var_int326(50000);
    cObject->set_var_int327(50000);
    cObject->set_var_int328(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);
    cObject->set_var_int645(99999999999900);
    cObject->set_var_int646(99999999999900);
    cObject->set_var_int647(99999999999900);
    cObject->set_var_int648(999999999999);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);
    cObject->set_var_float5(1.1);
    cObject->set_var_float6(1.1);
    cObject->set_var_float7(1.1);
    cObject->set_var_float8(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);
    cObject->set_var_double5(2.2);
    cObject->set_var_double6(2.2);
    cObject->set_var_double7(2.2);
    cObject->set_var_double8(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);
    cObject->set_var_bool5(true);
    cObject->set_var_bool6(true);
    cObject->set_var_bool7(true);
    cObject->set_var_bool8(true);

    cObject->set_var_string1(genRandomString(30));
    cObject->set_var_string2(genRandomString(30));
    cObject->set_var_string3(genRandomString(30));
    cObject->set_var_string4(genRandomString(30));
    cObject->set_var_string5(genRandomString(30));
    cObject->set_var_string6(genRandomString(30));
    cObject->set_var_string7(genRandomString(30));
    cObject->set_var_string8(genRandomString(30));
    return cObject;
}

static proto::ComplexObjectL1 *genComplexObjectL1() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL1 *cObject = new proto::ComplexObjectL1();
    cObject->set_var_int321(50000);
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);
    cObject->set_var_int323(50000);
    cObject->set_var_int324(50000);
    cObject->set_var_int325(50000);
    cObject->set_var_int326(50000);
    cObject->set_var_int327(50000);
    cObject->set_var_int328(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);
    cObject->set_var_int643(99999999999900);
    cObject->set_var_int644(99999999999900);
    cObject->set_var_int645(99999999999900);
    cObject->set_var_int646(99999999999900);
    cObject->set_var_int647(99999999999900);
    cObject->set_var_int648(999999999999);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);
    cObject->set_var_float3(1.1);
    cObject->set_var_float4(1.1);
    cObject->set_var_float5(1.1);
    cObject->set_var_float6(1.1);
    cObject->set_var_float7(1.1);
    cObject->set_var_float8(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);
    cObject->set_var_double3(2.2);
    cObject->set_var_double4(2.2);
    cObject->set_var_double5(2.2);
    cObject->set_var_double6(2.2);
    cObject->set_var_double7(2.2);
    cObject->set_var_double8(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);
    cObject->set_var_bool5(true);
    cObject->set_var_bool6(true);
    cObject->set_var_bool7(true);
    cObject->set_var_bool8(true);

    cObject->set_var_string1(genRandomString(30));
    cObject->set_var_string2(genRandomString(30));
    cObject->set_var_string3(genRandomString(30));
    cObject->set_var_string4(genRandomString(30));
    cObject->set_var_string5(genRandomString(30));
    cObject->set_var_string6(genRandomString(30));
    cObject->set_var_string7(genRandomString(30));
    cObject->set_var_string8(genRandomString(26));

    cObject->set_allocated_complexobjectl11(genComplexObjectL11());
    return cObject;
}



int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    int count = 0;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL1 *cObject = genComplexObjectL1();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::ComplexObjectL1 *dcObject = new proto::ComplexObjectL1();
        dcObject->ParseFromArray(buffer, bufferSize);
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
    cout << "ComplexObjectL1 avg serialization=" << avg << "  avg deserialize=" << avgd<< "   buffer size="<<bufferSize << endl;

    return 0;
}





