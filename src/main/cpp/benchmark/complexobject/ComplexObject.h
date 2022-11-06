#ifndef CPP_COMPLEXOBJECT_H
#define CPP_COMPLEXOBJECT_H
#include "ComplexObject1.h"

template<class T>
class ComplexObject {
private:
    int totalObjects = 5000000;
    int strLen;
    string randString;
    string genRandomString(int len);
    int objectLevel;

    ComplexObject1 *genComplexObject1();

    ComplexObject16 *genComplexObject16();

public:
    ComplexObject(int strLen, int objectLevel);

    void run();

};

template<class T>
void ComplexObject<T>::run() {
    long sum_serialization = 0;
    long sum_deserialization = 0;
    int bufferSize=0;
    randString = genRandomString(strLen);

    char * bu = new char[4096];
    T *cObject = nullptr;
    switch (objectLevel) {
        case 1:
            cObject = genComplexObject16();
            break;
    }

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
        T *dcOject = new T();
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
    cout << "Boost,"<<objectLevel<<"," << avg << "," << avgd<<","<<bufferSize<< endl;
}

template<class T>
string ComplexObject<T>::genRandomString(int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

template<class T>
ComplexObject<T>::ComplexObject(int strLen, int objectLevel):strLen(strLen), objectLevel(objectLevel) {}

template<class T>
ComplexObject1 *ComplexObject<T>::genComplexObject1() {
    ComplexObject1 *cObject = new ComplexObject1(randString);
    return cObject;
}

template<class T>
ComplexObject15 *ComplexObject<T>::genComplexObject15() {
    ComplexObject15 *cObject = new ComplexObject15(randString);
    return cObject;
}

template<class T>
ComplexObject16 *ComplexObject<T>::genComplexObject16() {
    ComplexObject16 *cObject = new ComplexObject16(randString);
    return cObject;
}

#endif //CPP_COMPLEXOBJECT_H


