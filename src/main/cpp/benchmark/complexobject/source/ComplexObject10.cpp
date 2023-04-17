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

#include "ComplexObject10.h"

ComplexObject10::~ComplexObject10() {
    delete complexObject;
}

char *ComplexObject10::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject10 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject10 *ComplexObject10::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject10 *boostObject = this;

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

char *ComplexObject10::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject10 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject10 *ComplexObject10::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject10 *boostObject = this;

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

char *ComplexObject10::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject10 *ComplexObject10::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject11();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject10::ComplexObject10(const string &varString) : var_string(varString) {}

ComplexObject10::ComplexObject10() {}

ComplexObject11 *ComplexObject10::getComplexObject() const {
    return complexObject;
}

void ComplexObject10::setComplexObject(ComplexObject11 *complexObject) {
    ComplexObject10::complexObject = complexObject;
}
