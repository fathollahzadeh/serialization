#include "ComplexObject14.h"

ComplexObject14::~ComplexObject14() {}

char *ComplexObject14::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject14 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject14::ComplexObject14(const string &varString) : var_string(varString) {}
