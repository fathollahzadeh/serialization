#include "ComplexObject6.h"

ComplexObject6::~ComplexObject6() {
    delete complexObject;
}

char *ComplexObject6::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject6 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject6 *ComplexObject6::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject6 *boostObject = this;

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

char *ComplexObject6::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject6 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject6 *ComplexObject6::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject6 *boostObject = this;

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

char *ComplexObject6::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject6 *ComplexObject6::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject7();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject6::ComplexObject6(const string &varString) : var_string(varString) {}

ComplexObject6::ComplexObject6() {}

ComplexObject7 *ComplexObject6::getComplexObject() const {
    return complexObject;
}

void ComplexObject6::setComplexObject(ComplexObject7 *complexObject) {
    ComplexObject6::complexObject = complexObject;
}
