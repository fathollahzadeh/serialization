#include "ComplexObject11.h"

ComplexObject11::~ComplexObject11() {

}

char *ComplexObject11::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject11 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject11::ComplexObject11(const string &varString) : var_string(varString) {}
