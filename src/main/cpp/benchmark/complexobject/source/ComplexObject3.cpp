#include "ComplexObject3.h"

ComplexObject3::~ComplexObject3() {

}

char *ComplexObject3::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject3 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject3::ComplexObject3(const string &varString) : var_string(varString) {}
