#include "ComplexObject12.h"

ComplexObject12::~ComplexObject12() {

}

char *ComplexObject12::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject12 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    char *tempBuffer = buffer;
    copyString(tempBuffer, ss.str(), objectSize);
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

ComplexObject12::ComplexObject12(const string &varString) : var_string(varString) {}

ComplexObject12::ComplexObject12() {}
