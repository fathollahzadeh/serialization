#include "ComplexObject9.h"

ComplexObject9::~ComplexObject9() {}


char *ComplexObject9::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject9 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject9 *ComplexObject9::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject9 *boostObject = this;

    //Create stream on heap: Keep stream alive:
    stringstream *rs = new stringstream();
    rs->write(buffer, bytesRead);

    //Create archive on heap: Keep stream alive:
    boost::archive::text_iarchive *ia = new boost::archive::text_iarchive(*rs, boost::archive::no_header);
    (*ia) >> boostObject;

    ia->delete_created_pointers();
    delete ia;
    delete rs;
    return boostObject;
}

ComplexObject9::ComplexObject9(const string &varString) : var_string(varString) {}

ComplexObject9::ComplexObject9() {}

ComplexObject10 *ComplexObject9::getComplexObject() const {
    return complexObject;
}

void ComplexObject9::setComplexObject(ComplexObject10 *complexObject) {
    ComplexObject9::complexObject = complexObject;
}
