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
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject4 *ComplexObject4::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject4 *boostObject = this;

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

ComplexObject4::ComplexObject4(const string &varString) : var_string(varString) {}

ComplexObject4::ComplexObject4() {}

ComplexObject5 *ComplexObject4::getComplexObject() const {
    return complexObject;
}

void ComplexObject4::setComplexObject(ComplexObject5 *complexObject) {
    ComplexObject4::complexObject = complexObject;
}
