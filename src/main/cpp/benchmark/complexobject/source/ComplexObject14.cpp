#include "ComplexObject14.h"

ComplexObject14::~ComplexObject14() {}

char *ComplexObject14::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject14 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject14 *ComplexObject14::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject14 *boostObject = this;

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

char *ComplexObject14::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject14 *ComplexObject14::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject15();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject14::ComplexObject14(const string &varString) : var_string(varString) {}

ComplexObject14::ComplexObject14() {}

ComplexObject15 *ComplexObject14::getComplexObject() const {
    return complexObject;
}

void ComplexObject14::setComplexObject(ComplexObject15 *complexObject) {
    ComplexObject14::complexObject = complexObject;
}
