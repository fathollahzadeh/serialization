#include "ComplexObject8.h"

ComplexObject8::~ComplexObject8() {}

char *ComplexObject8::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject8 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
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

ComplexObject8::ComplexObject8(const string &varString) : var_string(varString) {}

ComplexObject8::ComplexObject8() {}
