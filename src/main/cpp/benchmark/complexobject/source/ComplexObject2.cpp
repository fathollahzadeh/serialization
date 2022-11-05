#include "ComplexObject2.h"

ComplexObject2::~ComplexObject2() {

}

char *ComplexObject2::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject2 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject2::ComplexObject2(const string &varString) : var_string(varString) {}
