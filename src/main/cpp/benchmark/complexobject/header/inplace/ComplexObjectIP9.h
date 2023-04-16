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

#ifndef CPP_COMPLEXOBJECTIP9_H
#define CPP_COMPLEXOBJECTIP9_H


#include <Object.h>
#include "ComplexObjectIP10.h"
#include "ComplexObject9.h"

class ComplexObjectIP9 : public Object {

public:
    offset_ptr<char> var_string;
    offset_ptr<ComplexObjectIP10> complexObject;

    ComplexObjectIP9();

    ComplexObjectIP9(ComplexObject9 *object);

    void serialize(ComplexObject9 *complexObject);
};

#endif //CPP_COMPLEXOBJECTIP9_H
