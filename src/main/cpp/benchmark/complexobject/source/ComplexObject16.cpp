/*
* Copyright 2023 Saeed Fathollahzadeh. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

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

char *ComplexObject16::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject16 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject16 *ComplexObject16::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject16 *boostObject = this;

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
