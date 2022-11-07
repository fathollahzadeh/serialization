
#include "ComplexObject.h"

static ComplexObject1 *genComplexObject1();
static ComplexObject2 *genComplexObject2();
static ComplexObject3 *genComplexObject3();
static ComplexObject4 *genComplexObject4();
static ComplexObject5 *genComplexObject5();
static ComplexObject6 *genComplexObject6();
static ComplexObject7 *genComplexObject7();
static ComplexObject8 *genComplexObject8();
static ComplexObject9 *genComplexObject9();
static ComplexObject10 *genComplexObject10();
static ComplexObject11 *genComplexObject11();
static ComplexObject12 *genComplexObject12();
static ComplexObject13 *genComplexObject13();
static ComplexObject14 *genComplexObject14();
static ComplexObject15 *genComplexObject15();
static ComplexObject16 *genComplexObject16();

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

static ComplexObject1* genComplexObject1() {
    ComplexObject1 *cObject = new ComplexObject1(randString);
    cObject->setComplexObject(genComplexObject2());
    return cObject;
}

static ComplexObject2 *genComplexObject2() {
    ComplexObject2 *cObject = new ComplexObject2(randString);
    cObject->setComplexObject(genComplexObject3());
    return cObject;
}

static ComplexObject3 *genComplexObject3() {
    ComplexObject3 *cObject = new ComplexObject3(randString);
    cObject->setComplexObject(genComplexObject4());
    return cObject;
}
static ComplexObject4 *genComplexObject4() {
    ComplexObject4 *cObject = new ComplexObject4(randString);
    cObject->setComplexObject(genComplexObject5());
    return cObject;
}
static ComplexObject5 *genComplexObject5() {
    ComplexObject5 *cObject = new ComplexObject5(randString);
    cObject->setComplexObject(genComplexObject6());
    return cObject;
}
static ComplexObject6 *genComplexObject6() {
    ComplexObject6 *cObject = new ComplexObject6(randString);
    cObject->setComplexObject(genComplexObject7());
    return cObject;
}
static ComplexObject7 *genComplexObject7() {
    ComplexObject7 *cObject = new ComplexObject7(randString);
    cObject->setComplexObject(genComplexObject8());
    return cObject;
}
static ComplexObject8 *genComplexObject8() {
    ComplexObject8 *cObject = new ComplexObject8(randString);
    cObject->setComplexObject(genComplexObject9());
    return cObject;
}
static ComplexObject9 *genComplexObject9() {
    ComplexObject9 *cObject = new ComplexObject9(randString);
    cObject->setComplexObject(genComplexObject10());
    return cObject;
}
static ComplexObject10 *genComplexObject10() {
    ComplexObject10 *cObject = new ComplexObject10(randString);
    cObject->setComplexObject(genComplexObject11());
    return cObject;
}
static ComplexObject11 *genComplexObject11() {
    ComplexObject11 *cObject = new ComplexObject11(randString);
    cObject->setComplexObject(genComplexObject12());
    return cObject;
}
static ComplexObject12 *genComplexObject12() {
    ComplexObject12 *cObject = new ComplexObject12(randString);
    cObject->setComplexObject(genComplexObject13());
    return cObject;
}
static ComplexObject13 *genComplexObject13() {
    ComplexObject13 *cObject = new ComplexObject13(randString);
    cObject->setComplexObject(genComplexObject14());
    return cObject;
}
static ComplexObject14 *genComplexObject14() {
    ComplexObject14 *cObject = new ComplexObject14(randString);
    cObject->setComplexObject(genComplexObject15());
    return cObject;
}

static ComplexObject15 *genComplexObject15() {
    ComplexObject15 *cObject = new ComplexObject15(randString);
    cObject->setComplexObject(genComplexObject16());
    return cObject;
}

static ComplexObject16 *genComplexObject16() {
    ComplexObject16 *cObject = new  ComplexObject16(randString);
    return cObject;
}


int main(int argc, char *argv[]) {

    randString = genRandomString(1024);
    ComplexObject<ComplexObject16> co1(1, genComplexObject16());
    co1.run();
    //co1.runHandCoded();

    randString = genRandomString(512);
    ComplexObject<ComplexObject15> co2(2, genComplexObject15());
    co2.run();
   // co2.runHandCoded();
//
//    randString = genRandomString(256);
//    ComplexObject<ComplexObject13> co4(4, genComplexObject13());
//    co4.run();
//   // co4.runHandCoded();
//
//    randString = genRandomString(128);
//    ComplexObject<ComplexObject9> co8(8, genComplexObject9());
//    co8.run();
//    //co8.runHandCoded();
//
//    randString = genRandomString(64);
//    ComplexObject<ComplexObject1> co16(16, genComplexObject1());
//    co16.run();
    //co16.runHandCoded();

    return 0;
}