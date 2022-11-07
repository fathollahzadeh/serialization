#include "ComplexObject7.h"

ComplexObject7::~ComplexObject7() {
    delete complexObject;
}

char *ComplexObject7::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject7 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject7 *ComplexObject7::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject7 *boostObject = this;

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

char *ComplexObject7::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject7 *ComplexObject7::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject8();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject7::ComplexObject7(const string &varString) : var_string(varString) {}

ComplexObject7::ComplexObject7() {}

ComplexObject8 *ComplexObject7::getComplexObject() const {
    return complexObject;
}

void ComplexObject7::setComplexObject(ComplexObject8 *complexObject) {
    ComplexObject7::complexObject = complexObject;
}
