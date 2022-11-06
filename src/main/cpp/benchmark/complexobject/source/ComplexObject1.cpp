#include "ComplexObject1.h"

ComplexObject1::~ComplexObject1() {

}

char *ComplexObject1::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject1 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject1 *ComplexObject1::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject1 *boostObject = this;

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

ComplexObject1::ComplexObject1(const string &varString) : var_string(varString) {}

ComplexObject1::ComplexObject1() {}

ComplexObject2 *ComplexObject1::getComplexObject() const {
    return complexObject;
}

void ComplexObject1::setComplexObject(ComplexObject2 *complexObject) {
    ComplexObject1::complexObject = complexObject;
}


