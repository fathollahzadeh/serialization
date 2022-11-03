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
}

static proto::SimpleObject *genSimpleObject() {
    // Providing a seed value
    srand((unsigned) time(NULL));

    proto::SimpleObject *cObject = new proto::SimpleObject();
    cObject->set_var_int321(rand());
    cObject->set_var_int322(rand());
    cObject->set_var_int323(rand());
    cObject->set_var_int324(rand());
    cObject->set_var_int325(rand());
    cObject->set_var_int326(rand());
    cObject->set_var_int327(rand());
    cObject->set_var_int328(rand());
    cObject->set_var_int329(rand());
    cObject->set_var_int3210(rand());
    cObject->set_var_int3211(rand());
    cObject->set_var_int3212(rand());
    cObject->set_var_int3213(rand());
    cObject->set_var_int3214(rand());
    cObject->set_var_int3215(rand());
    cObject->set_var_int3216(rand());

    cObject->set_var_int641(rand());
    cObject->set_var_int642(rand());
    cObject->set_var_int643(rand());
    cObject->set_var_int644(rand());
    cObject->set_var_int645(rand());
    cObject->set_var_int646(rand());
    cObject->set_var_int647(rand());
    cObject->set_var_int648(rand());
    cObject->set_var_int649(rand());
    cObject->set_var_int6410(rand());
    cObject->set_var_int6411(rand());
    cObject->set_var_int6412(rand());
    cObject->set_var_int6413(rand());
    cObject->set_var_int6414(rand());
    cObject->set_var_int6415(rand());
    cObject->set_var_int6416(rand());

    cObject->set_var_float1(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float2(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float5(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float6(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float7(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float8(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float9(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float10(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float11(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float12(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float13(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float14(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float15(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    cObject->set_var_float16(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));


    cObject->set_var_double1(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double2(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double3(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double4(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double5(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double6(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double7(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double8(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double9(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double10(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double11(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double12(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double13(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double14(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double15(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));
    cObject->set_var_double16(static_cast <double > (rand()) / static_cast <double > (RAND_MAX));

    cObject->set_var_bool1(true);
    cObject->set_var_bool2(true);
    cObject->set_var_bool3(true);
    cObject->set_var_bool4(true);
    cObject->set_var_bool5(true);
    cObject->set_var_bool6(true);
    cObject->set_var_bool7(true);
    cObject->set_var_bool8(true);
    cObject->set_var_bool9(false);
    cObject->set_var_bool10(false);
    cObject->set_var_bool11(false);
    cObject->set_var_bool12(false);
    cObject->set_var_bool13(false);
    cObject->set_var_bool14(false);
    cObject->set_var_bool15(false);
    cObject->set_var_bool16(false);

    cObject->set_var_string1(genRandomString(39));
    cObject->set_var_string2(genRandomString(39));
    cObject->set_var_string3(genRandomString(39));
    cObject->set_var_string4(genRandomString(39));
    cObject->set_var_string5(genRandomString(39));
    cObject->set_var_string6(genRandomString(39));
    cObject->set_var_string7(genRandomString(39));
    cObject->set_var_string8(genRandomString(39));
    cObject->set_var_string9(genRandomString(39));
    cObject->set_var_string10(genRandomString(39));
    cObject->set_var_string11(genRandomString(39));
    cObject->set_var_string12(genRandomString(39));
    cObject->set_var_string13(genRandomString(39));
    cObject->set_var_string14(genRandomString(39));
    cObject->set_var_string15(genRandomString(39));
    cObject->set_var_string16(genRandomString(39));

    return cObject;
}


int main(int argc, char *argv[]) {

    int totalObjects = 10000;
    int count = 0;
    double sum_serialization;
    double sum_deserialization;

    for (int i = 0; i < totalObjects; ++i) {
        char *buffer = new char[1024];
        proto::SimpleObject *simpleObject = genSimpleObject();
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        simpleObject->SerializeToArray(buffer, 1024);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        proto::SimpleObject *dSimpleObject = new proto::SimpleObject();
        dSimpleObject->ParseFromArray(buffer, 1024);;
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
    cout << "SimpleObject avg serialization=" << avg << "  avg deserialize=" << avgd << endl;

    return 0;
}





