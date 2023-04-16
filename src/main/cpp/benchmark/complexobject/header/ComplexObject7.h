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

#ifndef CPP_COMPLEXOBJECT7_H
#define CPP_COMPLEXOBJECT7_H

#include "ComplexObject8.h"

class ComplexObject7 : public RootData {

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & var_string;
        ar & complexObject;
    }

public:
    string var_string;
    ComplexObject8 *complexObject;

    ComplexObject7();

    ComplexObject8 *getComplexObject() const;

    void setComplexObject(ComplexObject8 *complexObject);

    explicit ComplexObject7(const string &varString);

    virtual ~ComplexObject7();

    char *serializeBoost(char *buffer, int &objectSize);

    char *serializeBoostBinary(char *buffer, int &objectSize);

    ComplexObject7 *deserializeBoostBinary(char *buffer, int bytesRead);

    ComplexObject7 *deserializeBoost(char *buffer, int bytesRead);

    char *serializeHandcoded(char *buffer, int &objectSize);

    ComplexObject7 *deserializeHandcoded(char *buffer, int &bytesRead);
};

BOOST_CLASS_TRACKING(ComplexObject7, boost::serialization::track_never)


#endif //CPP_COMPLEXOBJECT7_H
