#include "ComplexObject6.h"

ComplexObject6::~ComplexObject6() {}

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

ComplexObject6::ComplexObject6(const string &varString) : var_string(varString) {}

ComplexObject6::ComplexObject6() {}
