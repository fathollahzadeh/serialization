#include "ComplexObject15.h"

ComplexObject15::~ComplexObject15() {
    delete complexObject;
}

char *ComplexObject15::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject15 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject15 *ComplexObject15::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject15 *boostObject = this;

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

char *ComplexObject15::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject15 *ComplexObject15::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject16();
    this->complexObject = this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject15::ComplexObject15(const string &varString) : var_string(varString) {}

ComplexObject15::ComplexObject15() {}

ComplexObject16 *ComplexObject15::getComplexObject() const {
    return complexObject;
}

void ComplexObject15::setComplexObject(ComplexObject16 *complexObject) {
    ComplexObject15::complexObject = complexObject;
}
