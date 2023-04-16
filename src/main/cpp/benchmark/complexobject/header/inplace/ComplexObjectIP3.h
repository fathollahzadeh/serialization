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

#ifndef CPP_COMPLEXOBJECTIP3_H
#define CPP_COMPLEXOBJECTIP3_H


#include <Object.h>
#include "ComplexObjectIP4.h"
#include "ComplexObject3.h"

class ComplexObjectIP3 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP4> complexObject;

    ComplexObjectIP3();

    ComplexObjectIP3(ComplexObject3 *object);

    void serialize(ComplexObject3 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP3_H
