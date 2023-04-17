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

#include "ComplexObject3.h"

ComplexObject3::~ComplexObject3() {
    delete complexObject;
}

char *ComplexObject3::serializeBoost(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject3 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::text_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject3 *ComplexObject3::deserializeBoost(char *buffer, int bytesRead) {

    ComplexObject3 *boostObject = this;

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

char *ComplexObject3::serializeBoostBinary(char *buffer, int &objectSize) {
    //Serialize:
    ComplexObject3 *T = this;

    //Serializer:
    stringstream ss;
    boost::archive::binary_oarchive oa(ss, boost::archive::no_header);
    oa << T;
    objectSize = ss.str().length();
    memcpy(buffer, ss.str().c_str(), objectSize);
    return buffer;
}

//Boost de-serialization:
ComplexObject3 *ComplexObject3::deserializeBoostBinary(char *buffer, int bytesRead) {

    ComplexObject3 *boostObject = this;

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


char *ComplexObject3::serializeHandcoded(char *buffer, int &objectSize) {
    buffer = copyString(buffer, this->var_string, objectSize);
    buffer = complexObject->serializeHandcoded(buffer, objectSize);
    return buffer;
}


ComplexObject3 *ComplexObject3::deserializeHandcoded(char *buffer, int &bytesRead) {
    parseString(buffer+ bytesRead, this->var_string);
    this->complexObject = new ComplexObject4();
    this->complexObject->deserializeHandcoded(buffer, bytesRead);
    return this;
}

ComplexObject3::ComplexObject3(const string &varString) : var_string(varString) {}

ComplexObject3::ComplexObject3() {}

ComplexObject4 *ComplexObject3::getComplexObject() const {
    return complexObject;
}

void ComplexObject3::setComplexObject(ComplexObject4 *complexObject) {
    ComplexObject3::complexObject = complexObject;
}
