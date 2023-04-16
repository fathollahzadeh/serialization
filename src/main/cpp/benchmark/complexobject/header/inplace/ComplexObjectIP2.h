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

#ifndef CPP_COMPLEXOBJECTIP2_H
#define CPP_COMPLEXOBJECTIP2_H


#include <Object.h>
#include "ComplexObjectIP3.h"
#include "ComplexObject2.h"

class ComplexObjectIP2 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP3> complexObject;

    ComplexObjectIP2();

    ComplexObjectIP2(ComplexObject2 *object);

    void serialize(ComplexObject2 *complexObject);
};


#endif //CPP_COMPLEXOBJECTIP2_H
