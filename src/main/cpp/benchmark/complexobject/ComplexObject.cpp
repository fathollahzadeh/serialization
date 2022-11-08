
#include "ComplexObject.h"
#include "ComplexObjectIP.h"

static string genRandomString(const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

static ComplexObject16 *genComplexObject16(std::string randString ) {
    ComplexObject16 *cObject = new  ComplexObject16(randString);
    return cObject;
}

static ComplexObject15 *genComplexObject15(std::string randString ) {
    ComplexObject15 *cObject = new ComplexObject15(randString);
    cObject->setComplexObject(genComplexObject16(randString));
    return cObject;
}
static ComplexObject14 *genComplexObject14(std::string randString ) {
    ComplexObject14 *cObject = new ComplexObject14(randString);
    cObject->setComplexObject(genComplexObject15(randString));
    return cObject;
}

static ComplexObject13 *genComplexObject13(std::string randString ) {
    ComplexObject13 *cObject = new ComplexObject13(randString);
    cObject->setComplexObject(genComplexObject14(randString));
    return cObject;
}

static ComplexObject12 *genComplexObject12(std::string randString ) {
    ComplexObject12 *cObject = new ComplexObject12(randString);
    cObject->setComplexObject(genComplexObject13(randString));
    return cObject;
}

static ComplexObject11 *genComplexObject11(std::string randString ) {
    ComplexObject11 *cObject = new ComplexObject11(randString);
    cObject->setComplexObject(genComplexObject12(randString));
    return cObject;
}

static ComplexObject10 *genComplexObject10(std::string randString ) {
    ComplexObject10 *cObject = new ComplexObject10(randString);
    cObject->setComplexObject(genComplexObject11(randString));
    return cObject;
}

static ComplexObject9 *genComplexObject9(std::string randString ) {
    ComplexObject9 *cObject = new ComplexObject9(randString);
    cObject->setComplexObject(genComplexObject10(randString));
    return cObject;
}

static ComplexObject8 *genComplexObject8(std::string randString ) {
    ComplexObject8 *cObject = new ComplexObject8(randString);
    cObject->setComplexObject(genComplexObject9(randString));
    return cObject;
}

static ComplexObject7 *genComplexObject7(std::string randString ) {
    ComplexObject7 *cObject = new ComplexObject7(randString);
    cObject->setComplexObject(genComplexObject8(randString));
    return cObject;
}
static ComplexObject6 *genComplexObject6(std::string randString ) {
    ComplexObject6 *cObject = new ComplexObject6(randString);
    cObject->setComplexObject(genComplexObject7(randString));
    return cObject;
}
static ComplexObject5 *genComplexObject5(std::string randString ) {
    ComplexObject5 *cObject = new ComplexObject5(randString);
    cObject->setComplexObject(genComplexObject6(randString));
    return cObject;
}
static ComplexObject4 *genComplexObject4(std::string randString ) {
    ComplexObject4 *cObject = new ComplexObject4(randString);
    cObject->setComplexObject(genComplexObject5(randString));
    return cObject;
}
static ComplexObject3 *genComplexObject3(std::string randString ) {
    ComplexObject3 *cObject = new ComplexObject3(randString);
    cObject->setComplexObject(genComplexObject4(randString));
    return cObject;
}
static ComplexObject2 *genComplexObject2(std::string randString ) {
    ComplexObject2 *cObject = new ComplexObject2(randString);
    cObject->setComplexObject(genComplexObject3(randString));
    return cObject;
}

static ComplexObject1* genComplexObject1(std::string randString ) {
    ComplexObject1 *cObject = new ComplexObject1(randString);
    cObject->setComplexObject(genComplexObject2(randString));
    return cObject;
}
int main(int argc, char *argv[]) {

    std::string randString1 = genRandomString(1024);
    std::string randString2 = genRandomString(512);
    std::string randString4 = genRandomString(256);
    std::string randString8 = genRandomString(128);
    std::string randString16 = genRandomString(64);

    ComplexObject<ComplexObject16> co1(1, genComplexObject16(randString1));
    co1.runBoost();
    co1.runHandCoded();

    ComplexObject<ComplexObject15> co2(2, genComplexObject15(randString2));
    co2.runBoost();
    co2.runHandCoded();

    ComplexObject<ComplexObject13> co4(4, genComplexObject13(randString4));
    co4.runBoost();
    co4.runHandCoded();

    ComplexObject<ComplexObject9> co8(8, genComplexObject9(randString8));
    co8.runBoost();
    co8.runHandCoded();

    ComplexObject<ComplexObject1> co16(16, genComplexObject1(randString16));
    co16.runBoost();
    co16.runHandCoded();

    ComplexObjectIP<ComplexObjectIP16, ComplexObject16> coIP1(1, genComplexObject16(randString1));
    coIP1.runInPlace();

    ComplexObjectIP<ComplexObjectIP15, ComplexObject15> coIP2(2, genComplexObject15(randString2));
    coIP2.runInPlace();

    ComplexObjectIP<ComplexObjectIP13, ComplexObject13> coIP4(4, genComplexObject13(randString4));
    coIP4.runInPlace();

    ComplexObjectIP<ComplexObjectIP9, ComplexObject9> coIP8(8, genComplexObject9(randString8));
    coIP8.runInPlace();

    ComplexObjectIP<ComplexObjectIP1, ComplexObject1> coIP16(16, genComplexObject1(randString16));
    coIP16.runInPlace();

    return 0;
}