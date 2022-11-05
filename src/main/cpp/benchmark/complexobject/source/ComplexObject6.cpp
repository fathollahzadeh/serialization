#include "ComplexObject6.h"

ComplexObject6::~ComplexObject6() {}

char *ComplexObject6::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject6 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject6::ComplexObject6(const string &varString) : var_string(varString) {}
