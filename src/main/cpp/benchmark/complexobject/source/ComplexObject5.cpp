#include "ComplexObject5.h"

ComplexObject5::~ComplexObject5() {
    delete complexObject;
}

char *ComplexObject5::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject5 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject5 *ComplexObject5::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject5 *boostObject = this;

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

char *ComplexObject5::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject5 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject5 *ComplexObject5::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject5 *boostObject = this;

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

char *ComplexObject5::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject5 *ComplexObject5::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject6();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject5::ComplexObject5(const string &varString) : var_string(varString) {}

ComplexObject5::ComplexObject5() {}

ComplexObject6 *ComplexObject5::getComplexObject() const {
    return complexObject;
}

void ComplexObject5::setComplexObject(ComplexObject6 *complexObject) {
    ComplexObject5::complexObject = complexObject;
}
