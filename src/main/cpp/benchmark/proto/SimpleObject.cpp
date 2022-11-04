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

#include "SimpleObject.pb.h"
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

static proto::SimpleObject *genSimpleObject() {
    proto::SimpleObject *cObject = new proto::SimpleObject();
    cObject->set_var_string(genRandomString(1024));
    return cObject;
}
int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    double sum_serialization;
    double sum_deserialization;
    size_t bufferSize;

    for (int i = 0; i < totalObjects; ++i) {
        proto::SimpleObject *cObject = genSimpleObject();
        bufferSize = cObject->ByteSizeLong();
        char *buffer = new char[bufferSize];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->SerializeToArray(buffer, bufferSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::SimpleObject *dcObject = new proto::SimpleObject();
        dcObject->ParseFromArray(buffer, bufferSize);;
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();

        delete cObject;
        delete dcObject;
        delete[] buffer;
    }
    double avg = sum_serialization / totalObjects;
    double avgd = sum_deserialization / totalObjects;
    cout << "Proto SimpleObject avg serialization=" << avg << "  avg deserialize=" << avgd << "   buffer size="<<bufferSize<< endl;

    return 0;
}





