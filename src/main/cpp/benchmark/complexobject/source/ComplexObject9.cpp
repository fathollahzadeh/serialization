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

#include "ComplexObject9.h"

ComplexObject9::~ComplexObject9() {
    delete complexObject;
}


char *ComplexObject9::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject9 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject9 *ComplexObject9::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject9 *boostObject = this;

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

char *ComplexObject9::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject9 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject9 *ComplexObject9::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject9 *boostObject = this;

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

char *ComplexObject9::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject9 *ComplexObject9::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject10();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject9::ComplexObject9(const string &varString) : var_string(varString) {}

ComplexObject9::ComplexObject9() {}

ComplexObject10 *ComplexObject9::getComplexObject() const {
    return complexObject;
}

void ComplexObject9::setComplexObject(ComplexObject10 *complexObject) {
    ComplexObject9::complexObject = complexObject;
}
