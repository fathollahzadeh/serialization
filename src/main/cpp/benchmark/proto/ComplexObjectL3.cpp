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

#include "ComplexObjectL3.pb.h"
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

static proto::ComplexObjectL37 *genComplexObjectL37() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL37 *cObject = new proto::ComplexObjectL37();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    return cObject;
}

static proto::ComplexObjectL36 *genComplexObjectL36() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL36 *cObject = new proto::ComplexObjectL36();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl37(genComplexObjectL37());
    return cObject;
}

static proto::ComplexObjectL35 *genComplexObjectL35() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL35 *cObject = new proto::ComplexObjectL35();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl36(genComplexObjectL36());

    return cObject;
}

static proto::ComplexObjectL34 *genComplexObjectL34() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL34 *cObject = new proto::ComplexObjectL34();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl35(genComplexObjectL35());

    return cObject;
}

static proto::ComplexObjectL33 *genComplexObjectL33() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL33 *cObject = new proto::ComplexObjectL33();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl34(genComplexObjectL34());

    return cObject;
}

static proto::ComplexObjectL32 *genComplexObjectL32() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL32 *cObject = new proto::ComplexObjectL32();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl33(genComplexObjectL33());
    return cObject;
}
static proto::ComplexObjectL31 *genComplexObjectL31() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL31 *cObject = new proto::ComplexObjectL31();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));

    cObject->set_allocated_complexobjectl32(genComplexObjectL32());
    return cObject;
}

static proto::ComplexObjectL3 *genComplexObjectL3() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::ComplexObjectL3 *cObject = new proto::ComplexObjectL3();
    cObject->set_var_int321(50000);
    cObject->set_var_int322(50000);

    cObject->set_var_int641(99999999999900);
    cObject->set_var_int642(99999999999900);

    cObject->set_var_float1(1.1);
    cObject->set_var_float2(1.1);

    cObject->set_var_double1(2.2);
    cObject->set_var_double2(2.2);

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));
    cObject->set_allocated_complexobjectl31(genComplexObjectL31());
    return cObject;
}

int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    int count = 0;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL3 *cObject = genComplexObjectL3();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::ComplexObjectL3 *dcObject = new proto::ComplexObjectL3();
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
    cout << "ComplexObjectL3 avg serialization=" << avg << "  avg deserialize=" << avgd << "   buffer size="<<bufferSize<< endl;

    return 0;
}





