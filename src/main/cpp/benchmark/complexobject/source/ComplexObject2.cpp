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
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject2 *ComplexObject2::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject2 *boostObject = this;

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

ComplexObject2::ComplexObject2(const string &varString) : var_string(varString) {}

ComplexObject2::ComplexObject2() {}

ComplexObject3 *ComplexObject2::getComplexObject() const {
    return complexObject;
}

void ComplexObject2::setComplexObject(ComplexObject3 *complexObject) {
    ComplexObject2::complexObject = complexObject;
}
