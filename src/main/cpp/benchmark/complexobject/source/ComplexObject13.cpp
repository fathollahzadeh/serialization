#include "ComplexObject13.h"

ComplexObject13::~ComplexObject13() {
    delete complexObject;
}

char *ComplexObject13::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject13 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject13 *ComplexObject13::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject13 *boostObject = this;

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

char *ComplexObject13::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject13 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject13 *ComplexObject13::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject13 *boostObject = this;

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

char *ComplexObject13::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject13 *ComplexObject13::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject14();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject13::ComplexObject13(const string &varString) : var_string(varString) {}

ComplexObject13::ComplexObject13() {}

ComplexObject14 *ComplexObject13::getComplexObject() const {
    return complexObject;
}

void ComplexObject13::setComplexObject(ComplexObject14 *complexObject) {
    ComplexObject13::complexObject = complexObject;
}
