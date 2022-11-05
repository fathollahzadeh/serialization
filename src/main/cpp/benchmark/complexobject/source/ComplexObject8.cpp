#include "ComplexObject8.h"

ComplexObject8::~ComplexObject8() {}

char *ComplexObject8::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject8 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject8::ComplexObject8(const string &varString) : var_string(varString) {}
