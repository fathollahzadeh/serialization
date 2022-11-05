#include "ComplexObject9.h"

ComplexObject9::~ComplexObject9() {

}


char *ComplexObject9::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject9 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
    return buffer;
}

ComplexObject9::ComplexObject9(const string &varString) : var_string(varString) {}
