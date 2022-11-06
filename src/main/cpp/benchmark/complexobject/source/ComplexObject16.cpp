#include "ComplexObject16.h"

ComplexObject16::~ComplexObject16() {}

char *ComplexObject16::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject16 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject16 *ComplexObject16::deserializeBoost(char *buffer, int bytesRead) {
    ComplexObject16 *boostObject = this;

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

char *ComplexObject16::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    return buffer;
}


ComplexObject16 *ComplexObject16::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer, this->var_string);
    bytesRead += (sizeof(int) + this->var_string.length());
    return this;
}


ComplexObject16::ComplexObject16(const string &varString) : var_string(varString) {}

ComplexObject16::ComplexObject16() {}
