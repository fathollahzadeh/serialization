#include "ComplexObject8.h"

ComplexObject8::~ComplexObject8() {
    delete complexObject;
}

char *ComplexObject8::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject8 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject8 *ComplexObject8::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject8 *boostObject = this;

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

char *ComplexObject8::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject8 *ComplexObject8::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject9();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject8::ComplexObject8(const string &varString) : var_string(varString) {}

ComplexObject8::ComplexObject8() {}

ComplexObject9 *ComplexObject8::getComplexObject() const {
    return complexObject;
}

void ComplexObject8::setComplexObject(ComplexObject9 *complexObject) {
    ComplexObject8::complexObject = complexObject;
}
