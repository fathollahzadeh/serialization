#include "ComplexObject12.h"

ComplexObject12::~ComplexObject12() {

}

char *ComplexObject12::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject12 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject12::ComplexObject12(const string &varString) : var_string(varString) {}
