#include "ComplexObject10.h"

ComplexObject10::~ComplexObject10() {

}

char *ComplexObject10::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject10 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject10::ComplexObject10(const string &varString) : var_string(varString) {}
