/*
* Copyright 2023 Saeed Fathollahzadeh. All rights reserved.
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

#include "ComplexObjectL4.pb.h"
#include <random>
#include <chrono>


using namespace std;

std::string randString = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0";

static string genRandomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

static proto::ComplexObjectL415 *genComplexObjectL415() {
    proto::ComplexObjectL415 *cObject = new proto::ComplexObjectL415();
    cObject->set_var_string(randString);
    return cObject;
}

static proto::ComplexObjectL414 *genComplexObjectL414() {
    proto::ComplexObjectL414 *cObject = new proto::ComplexObjectL414();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL415());
    return cObject;
}

static proto::ComplexObjectL413 *genComplexObjectL413() {
    proto::ComplexObjectL413 *cObject = new proto::ComplexObjectL413();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL414());
    return cObject;
}

static proto::ComplexObjectL412 *genComplexObjectL412() {
    proto::ComplexObjectL412 *cObject = new proto::ComplexObjectL412();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL413());
    return cObject;
}

static proto::ComplexObjectL411 *genComplexObjectL411() {
    proto::ComplexObjectL411 *cObject = new proto::ComplexObjectL411();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL412());
    return cObject;
}

static proto::ComplexObjectL410 *genComplexObjectL410() {
    proto::ComplexObjectL410 *cObject = new proto::ComplexObjectL410();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL411());
    return cObject;
}

static proto::ComplexObjectL49 *genComplexObjectL49() {
    proto::ComplexObjectL49 *cObject = new proto::ComplexObjectL49();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL410());
    return cObject;
}

static proto::ComplexObjectL48 *genComplexObjectL48() {
    proto::ComplexObjectL48 *cObject = new proto::ComplexObjectL48();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL49());
    return cObject;
}

static proto::ComplexObjectL47 *genComplexObjectL47() {
    proto::ComplexObjectL47 *cObject = new proto::ComplexObjectL47();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL48());
    return cObject;
}

static proto::ComplexObjectL46 *genComplexObjectL46() {
    proto::ComplexObjectL46 *cObject = new proto::ComplexObjectL46();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL47());
    return cObject;
}

static proto::ComplexObjectL45 *genComplexObjectL45() {
    proto::ComplexObjectL45 *cObject = new proto::ComplexObjectL45();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL46());
    return cObject;
}

static proto::ComplexObjectL44 *genComplexObjectL44() {
    proto::ComplexObjectL44 *cObject = new proto::ComplexObjectL44();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL45());
    return cObject;
}

static proto::ComplexObjectL43 *genComplexObjectL43() {
    proto::ComplexObjectL43 *cObject = new proto::ComplexObjectL43();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL44());
    return cObject;
}

static proto::ComplexObjectL42 *genComplexObjectL42() {
    proto::ComplexObjectL42 *cObject = new proto::ComplexObjectL42();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL43());
    return cObject;
}

static proto::ComplexObjectL41 *genComplexObjectL41() {
    proto::ComplexObjectL41 *cObject = new proto::ComplexObjectL41();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL42());
    return cObject;
}

static proto::ComplexObjectL4 *genComplexObjectL4() {
    proto::ComplexObjectL4 *cObject = new proto::ComplexObjectL4();
    cObject->set_var_string(randString);
    cObject->set_allocated_complexobject(genComplexObjectL41());
    return cObject;
}

static void run1(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    randString = genRandomString(1024);

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL415 *cObject = genComplexObjectL415();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto *dcObject = new proto::ComplexObjectL415();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "ProtoBuf,1," << avg << "," << avgd<<","<<bufferSize<< endl;

}

static void run2(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    randString = genRandomString(512);

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL414 *cObject = genComplexObjectL414();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto *dcObject = new proto::ComplexObjectL414();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "ProtoBuf,2," << avg << "," << avgd<<","<<bufferSize<< endl;

}

static void run4(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    randString = genRandomString(256);

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL412 *cObject = genComplexObjectL412();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto *dcObject = new proto::ComplexObjectL412();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "ProtoBuf,3," << avg << "," << avgd<<","<<bufferSize<< endl;

}

static void run8(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    randString = genRandomString(128);

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL48 *cObject = genComplexObjectL48();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto *dcObject = new proto::ComplexObjectL48();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "ProtoBuf,4," << avg << "," << avgd<<","<<bufferSize<< endl;

}

static void run16(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    size_t bufferSize;
    randString = genRandomString(64);

    for (int i = 0; i < totalObjects; ++i) {
        proto::ComplexObjectL4 *cObject = genComplexObjectL4();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        auto *dcObject = new proto::ComplexObjectL4();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "ProtoBuf,5," << avg << "," << avgd<<","<<bufferSize<< endl;
}

int main(int argc, char *argv[]) {
    run1();
    run2();
    run4();
    run8();
    run16();

    return 0;
}







