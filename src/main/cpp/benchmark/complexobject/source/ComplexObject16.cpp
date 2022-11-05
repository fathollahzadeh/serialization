#include "ComplexObject16.h"

ComplexObject16::~ComplexObject16() {}

char *ComplexObject16::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject16 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject16::ComplexObject16(const string &varString) : var_string(varString) {}
