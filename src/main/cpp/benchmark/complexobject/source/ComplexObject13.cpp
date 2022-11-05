#include "ComplexObject13.h"

ComplexObject13::~ComplexObject13() {}

char *ComplexObject13::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject13 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject13::ComplexObject13(const string &varString) : var_string(varString) {}
