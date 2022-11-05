#include "ComplexObject4.h"

ComplexObject4::~ComplexObject4() {

}

char *ComplexObject4::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject4 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject4::ComplexObject4(const string &varString) : var_string(varString) {}
