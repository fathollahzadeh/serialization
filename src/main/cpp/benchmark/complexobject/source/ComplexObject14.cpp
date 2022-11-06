#include "ComplexObject14.h"

ComplexObject14::~ComplexObject14() {}

char *ComplexObject14::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject14 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
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

ComplexObject14::ComplexObject14(const string &varString) : var_string(varString) {}

ComplexObject14::ComplexObject14() {}
