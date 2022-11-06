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
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject11 *ComplexObject11::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject11 *boostObject = this;

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

ComplexObject11::ComplexObject11(const string &varString) : var_string(varString) {}

ComplexObject11::ComplexObject11() {}

ComplexObject12 *ComplexObject11::getComplexObject() const {
    return complexObject;
}

void ComplexObject11::setComplexObject(ComplexObject12 *complexObject) {
    ComplexObject11::complexObject = complexObject;
}
