#include "ComplexObject5.h"

ComplexObject5::~ComplexObject5() {}

char *ComplexObject5::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject5 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject5::ComplexObject5(const string &varString) : var_string(varString) {}
