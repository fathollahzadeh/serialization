#ifndef CPP_COMPLEXOBJECTIP_H
#define CPP_COMPLEXOBJECTIP_H

#include "ComplexObject1.h"
#include "thread"
#include "Object.h"
#include "ComplexObjectIP1.h"

template<class T, class S>
class ComplexObjectIP {
private:
    int totalObjects = 1000000;
    string randString;
    int objectLevel;
    S *vObject;

public:
    ComplexObjectIP(int objectLevel, T *cObject);

    ComplexObjectIP(int objectLevel, S *vObject);

    void runInPlace();
};

template<class T, class S>
void ComplexObjectIP<T,S>::runInPlace() {
    long sum_serialization = 0;
    long sum_deserialization = 0;
    char *bu = new char[4096];
    thread::id this_id = this_thread::get_id();
    Allocator allocator;
    allocator.setUp(bu, 4096);
    Object::allocator[this_id] = allocator;

    int objectSize;
    int sizeofObject = sizeof(objectSize);

    //Define a pointer for size of object:
    char *tPoint;

    // reserve space for object size:
    tPoint = bu;
    Object::allocator[this_id].setBytesUsed( sizeofObject);

    //Serialize object:
    new T(vObject);
    objectSize = Object::allocator[this_id].getBytesUsed() - sizeofObject;

    //Set object size in the reserved place:
    new(tPoint)int(objectSize);

    delete[] tPoint;
    Object::allocator[this_id].setBytesUsed(0);

    for (int i = 0; i < totalObjects; ++i) {
        char *buffer = new char[objectSize];
        tPoint = buffer;
        allocator.setUp(buffer, objectSize);
        Object::allocator[this_id] = allocator;

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        new T(vObject);
        new(tPoint)int(objectSize);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::steady_clock::time_point begind = std::chrono::steady_clock::now();
        int dObjectSize = *(int *) tPoint;
        T *dcObject = (T *) tPoint+sizeof(objectSize);
        std::chrono::steady_clock::time_point endd = std::chrono::steady_clock::now();
        sum_serialization += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sum_deserialization += std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count();
        delete[] tPoint;

    }
    //delete cObject;
    double avg = (double) sum_serialization / totalObjects;
    double avgd = (double) sum_deserialization / totalObjects;
    cout << "inPlace," << objectLevel << "," << avg << "," << avgd << "," << objectSize<<",1024,"<<(objectSize-1024) << endl;
}

template<class T, class S>
ComplexObjectIP<T, S>::ComplexObjectIP(int objectLevel, S *vObject):objectLevel(objectLevel), vObject(vObject) {}


#endif //CPP_COMPLEXOBJECTIP_H


