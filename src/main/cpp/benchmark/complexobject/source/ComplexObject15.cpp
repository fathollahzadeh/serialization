#include "ComplexObject15.h"

ComplexObject15::~ComplexObject15() {}

char *ComplexObject15::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject15 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject15::ComplexObject15(const string &varString) : var_string(varString) {}
