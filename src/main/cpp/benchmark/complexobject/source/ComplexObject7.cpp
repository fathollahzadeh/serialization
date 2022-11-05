#include "ComplexObject7.h"

ComplexObject7::~ComplexObject7() {

}

char *ComplexObject7::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject7 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject7::ComplexObject7(const string &varString) : var_string(varString) {}
