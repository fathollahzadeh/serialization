#include "ComplexObject12.h"

ComplexObject12::~ComplexObject12() {
    delete complexObject;
}

char *ComplexObject12::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject12 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject12 *ComplexObject12::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject12 *boostObject = this;

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

char *ComplexObject12::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject12 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject12 *ComplexObject12::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject12 *boostObject = this;

    //Create stream on heap: Keep stream alive:
    stringstream *rs = new stringstream();
    rs->write(buffer, bytesRead);

    //Create archive on heap: Keep stream alive:
    boost::archive::binary_iarchive *ia = new boost::archive::binary_iarchive(*rs, boost::archive::no_header);
    (*ia) >> boostObject;

    ia->delete_created_pointers();
    delete ia;
    delete rs;
    return boostObject;
}

char *ComplexObject12::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject12 *ComplexObject12::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject13();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject12::ComplexObject12(const string &varString) : var_string(varString) {}

ComplexObject12::ComplexObject12() {}

ComplexObject13 *ComplexObject12::getComplexObject() const {
    return complexObject;
}

void ComplexObject12::setComplexObject(ComplexObject13 *complexObject) {
    ComplexObject12::complexObject = complexObject;
}
