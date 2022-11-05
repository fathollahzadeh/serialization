#include "ComplexObject1.h"

ComplexObject1::ComplexObject1() {}

ComplexObject1::~ComplexObject1() {}

char *ComplexObject1::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject1 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject1::ComplexObject1(const string &varString) : var_string(varString) {}


