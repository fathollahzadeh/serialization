#include "ComplexObject1.h"

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

static ComplexObject16 *genComplexObject16() {
    ComplexObject16 *cObject = new ComplexObject16(randString);
    return cObject;
}

static void run1(){
    int totalObjects = 5000000;
    long sum_serialization = 0;
    long sum_deserialization = 0;
    int bufferSize=0;
    randString = genRandomString(1024);

    char * bu = new char[4096];
    ComplexObject16 *cObject = genComplexObject16();
    cObject->serializeBoost(bu,bufferSize);
    delete[] bu;

    cout<<"Size = "<< bufferSize<<endl;
    for (int i = 0; i < totalObjects; ++i) {
        int tmpSize = 0;
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->serializeBoost(buffer, tmpSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        ComplexObject16 *dcOject = new ComplexObject16();
        dcOject->deserializeBoost(buffer, bufferSize);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        delete[] buffer;
        delete dcOject;
    }
    delete cObject;
    double avg = (double )sum_serialization / totalObjects;
    double avgd = (double )sum_deserialization / totalObjects;
    cout << "Boost,1," << avg << "," << avgd<<","<<bufferSize<< endl;

}

int main(int argc, char *argv[]) {

    run1();
    return 0;
}