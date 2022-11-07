#include "ComplexObject10.h"

ComplexObject10::~ComplexObject10() {
    delete complexObject;
}

char *ComplexObject10::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject10 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject10 *ComplexObject10::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject10 *boostObject = this;

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

char *ComplexObject10::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject10 *ComplexObject10::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject11();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject10::ComplexObject10(const string &varString) : var_string(varString) {}

ComplexObject10::ComplexObject10() {}

ComplexObject11 *ComplexObject10::getComplexObject() const {
    return complexObject;
}

void ComplexObject10::setComplexObject(ComplexObject11 *complexObject) {
    ComplexObject10::complexObject = complexObject;
}
