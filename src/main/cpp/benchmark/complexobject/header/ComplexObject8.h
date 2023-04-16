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

#ifndef CPP_COMPLEXOBJECT8_H
#define CPP_COMPLEXOBJECT8_H

#include "ComplexObject9.h"

class ComplexObject8 : public RootData {

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject9 *complexObject;
    ComplexObject8();

    ComplexObject9 *getComplexObject() const;

    void setComplexObject(ComplexObject9 *complexObject);

    explicit ComplexObject8(const string &varString);

    virtual ~ComplexObject8();

    char *serializeBoost(char *buffer, int &objectSize);

    ComplexObject8 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject8 *deserializeBoostBinary(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject8 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject8, boost::serialization::track_never)

#endif //CPP_COMPLEXOBJECT8_H
