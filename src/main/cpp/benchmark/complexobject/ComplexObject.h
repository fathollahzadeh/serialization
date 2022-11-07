#ifndef CPP_COMPLEXOBJECT_H
#define CPP_COMPLEXOBJECT_H

#include "ComplexObject1.h"

template<class T>
class ComplexObject {
private:
    int totalObjects = 1000000;
    string randString;
    int objectLevel;
    T *cObject;

public:
    ComplexObject(int objectLevel, T *cObject);

    void run();

    void runHandCoded();
};

template<class T>
void ComplexObject<T>::run() {
    long sum_serialization = 0;
    long sum_deserialization = 0;
    int bufferSize = 0;
    char *bu = new char[4096];
    cObject->serializeBoost(bu, bufferSize);
    delete[] bu;

    for (int i = 0; i < totalObjects; ++i) {
        int tmpSize = 0;
        char *buffer = new char[bufferSize];
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        cObject->serializeBoost(buffer, tmpSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        char *tmpPointer = buffer;
        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        T *dcOject = new T();
        dcOject = dcOject->deserializeBoost(buffer, bufferSize);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();

        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        delete[] tmpPointer;
        delete dcOject;
    }
    double avg = (double) sum_serialization / totalObjects;
    double avgd = (double) sum_deserialization / totalObjects;
    cout << "Boost," << objectLevel << "," << avg << "," << avgd << "," << bufferSize << endl;
}

template<class T>
void ComplexObject<T>::runHandCoded() {
    long sum_serialization = 0;
    long sum_deserialization = 0;
    int bufferSize = 0;
    char *bu = new char[4096];
    cObject->serializeHandcoded(bu, bufferSize);
    delete[] bu;

    for (int i = 0; i < totalObjects; ++i) {
        int tmpSize = 0;
        char *buffer = new char[bufferSize];
        char *tmpPointer = buffer;
        char *tmpBuffer = buffer;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        buffer = cObject->serializeHandcoded(buffer, tmpSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        tmpSize = 0;
        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        T dcOject;
        dcOject.deserializeHandcoded(tmpBuffer, tmpSize);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();
        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        delete[] tmpPointer;
    }
    //delete cObject;
    double avg = (double) sum_serialization / totalObjects;
    double avgd = (double) sum_deserialization / totalObjects;
    cout << "Hand-coded," << objectLevel << "," << avg << "," << avgd << "," << bufferSize << endl;
}

template<class T>
ComplexObject<T>::ComplexObject(int objectLevel, T *cObject):objectLevel(objectLevel), cObject(cObject) {}


#endif //CPP_COMPLEXOBJECT_H


